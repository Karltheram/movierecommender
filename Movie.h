#include <iostream>
#include <vector>
#include <string>
#include <string>
#include<bits/stdc++.h>

using namespace std;
class Movie {
public:
    string _id;
    string _title;
    string _genres;
    string _originalLanguage;
    string _overview;
    string _popularity;
    string _productionCompany;
    string _releaseDate;
    string _budget;
    string _revenue;
    string _runTime;
    string _status;
    string _tagline;
    string _voteAverage;
    string _voteCount;
    string _poster;
    string _backdrop;
    int movieCount = 0;
    vector<Movie> rolodex;

    Movie() = default;;

    Movie(string id, string title, string genre, string originalLanguage, string overview, string popularity,
          string productionCompany, string releaseDate,
          string budget, string revenue, string runTime, string status, string tagline, string voteAverage,
          string voteCount, string poster, string backdrop) {

        _id = id;
        _title = title;
        _genres = genre;
        _originalLanguage = originalLanguage;
        _overview = overview;
        _popularity = popularity;
        _productionCompany = productionCompany;
        _releaseDate = releaseDate;
        _budget = budget;
        _revenue = revenue;
        _runTime = runTime;
        _status = status;
        _tagline = tagline;
        _voteAverage = voteAverage;
        _voteCount = voteCount;
        _poster = poster;
        _backdrop = backdrop;
    }


    void fileReader(const string& dataset)
    {
        ifstream inFile(dataset);
        if (inFile.is_open()) {

            /// header titles
            string temp_id;
            string title;
            string genre;
            string originalLanguage;
            string overview;
            string temp_popularity;
            string productionCompany;
            string releaseDate;
            string temp_budget;
            string temp_revenue;
            string temp_runtime;
            string status;
            string tagline;
            string temp_voteAverage;
            string temp_voteCount;
            string poster;
            string backdrop;

            /// ignore header
            string header;
            getline(inFile, header);

            /// grab essentials
            while (!inFile.eof()) {
                getline(inFile, temp_id, ',');
                getline(inFile, title, ',');
                getline(inFile, genre, ',');
                getline(inFile, originalLanguage, ',');
                getline(inFile, overview, ',');
                getline(inFile, temp_popularity, ',');
                getline(inFile, productionCompany, ',');
                getline(inFile, releaseDate, ',');
                getline(inFile, temp_budget, ',');
                getline(inFile, temp_revenue, ',');
                getline(inFile, temp_runtime, ',');
                getline(inFile, status, ',');
                getline(inFile, tagline, ',');
                getline(inFile, temp_voteAverage, ',');
                getline(inFile, temp_voteCount, ',');
                getline(inFile, poster, ',');
                getline(inFile, backdrop, '\n');

                Movie bundle(temp_id, title, genre, originalLanguage, overview, temp_popularity, productionCompany,
                             releaseDate,
                             temp_budget, temp_revenue, temp_runtime, status, tagline, temp_voteAverage, temp_voteCount,
                             poster, backdrop);
                rolodex.push_back(bundle);
                movieCount++;
            }
        }
    }

    void prinObject(const Movie& object)
    {
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "Movie - " << object._title << " (ID: " << object._id << ")" << endl << "Runtime: (" << object._runTime << " minutes)" << endl;
        cout << "Genres: ";
        cout << object._genres;
        cout << endl << "\nTagline: " << object._tagline << endl;
        cout << "Language (" << object._originalLanguage << "), " << "Released (" << object._releaseDate << "), " << "Budget: " << object._budget << " Revenue: " << object._revenue << endl;
        cout << "Popularity of Movie: " << object._popularity << " is based on " << object._voteAverage << " voting average from " << object._voteCount << " voters!" << endl;
    }
};

///=====================================================================================================================

class Map {
    class TreeNode {
    public:
        int uniqueID{};
        string Name;
        Movie Object;
        TreeNode *left{};
        TreeNode *right{};
    };

    TreeNode *theNode;

    void inorderIDtraversal(TreeNode *root, vector<Movie> &id)
    {
        if (root != nullptr) {
            inorderIDtraversal(root->left, id);
            id.push_back(root->Object);
            inorderIDtraversal(root->right, id);
        }
    }

    vector<Movie> inorderIDstorer(TreeNode *root)
    {
        vector<Movie> id;
        inorderIDtraversal(root, id);
        return id;
    }


    int max(int left, int right)
    {
        return (left > right) ? left : right;
    }

    /// (Stepik)
    int heightofnode(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        else {
            int leftHeight = heightofnode(root->left);
            int rightHeight = heightofnode(root->right);
            return max(leftHeight, rightHeight) + 1;
        }
    }

    /// (Stepik)
    bool isAVL(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        int leftHeight = heightofnode(root->left);
        int rightHeight = heightofnode(root->right);

        if (abs(leftHeight - rightHeight) <= 1
            && isAVL(root->left) && isAVL(root->right))
            return true;
        return false;
    }

    /// (Stepik)
    TreeNode *rotateLeft(TreeNode *node)
    {
        TreeNode *rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        return rightChild;
    }

    TreeNode *rotateRight(TreeNode *node)
    {
        TreeNode *leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        return leftChild;
    }

    TreeNode *rotateLeftRight(TreeNode *node)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    TreeNode *rotateRightLeft(TreeNode *node)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    TreeNode *newnodestring(string name,Movie object)
    {
        auto *node = new TreeNode();
        node->uniqueID = 0;
        node->left = nullptr;
        node->right = nullptr;
        node->Object=object;
        node->Name = name;
        return (node);
    }

    TreeNode *newnodenumber(int key, Movie object)
    {
        auto *node = new TreeNode();
        node->uniqueID = key;
        node->left = nullptr;
        node->right = nullptr;
        node->Object=object;
        node->Name = "";
        return (node);
    }

    TreeNode *thestringinsert(TreeNode *root, string name, Movie object)
    {
        if (root == nullptr) {
            return (newnodestring(name,object));
        }
        if (root->Name < name) {
            root->right = thestringinsert(root->right, name,object);
            bool balancerchecker = isAVL(root);
            if (!balancerchecker) {
                if (name > root->right->Name) {
                    root = rotateLeft(root);
                }
                else {
                    root = rotateRightLeft(root);
                }
            }
        }
        else if (root->Name > name) {
            root->left = thestringinsert(root->left, name,object);
            bool balancerchecker = isAVL(root);
            if (!balancerchecker) {
                if (name < root->left->Name) {
                    root = rotateRight(root);
                }
                else {
                    root = rotateLeftRight(root);
                }
            }
        }
        return root;
    }

    TreeNode *thenmumberinsert(TreeNode *root, int key, Movie object)
    {
        if (root == nullptr) {
            return (newnodenumber(key, object));
        }
        if (root->uniqueID < key) {
            root->right = thenmumberinsert(root->right, key, object);
            bool balancerchecker = isAVL(root);
            if (!balancerchecker) {
                if (key > root->right->uniqueID) {
                    root = rotateLeft(root);
                }
                else {
                    root = rotateRightLeft(root);
                }
            }
        }
        else if (root->uniqueID > key) {
            root->left = thenmumberinsert(root->left, key, object);
            bool balancerchecker = isAVL(root);
            if (!balancerchecker) {
                if (key < root->left->uniqueID) {
                    root = rotateRight(root);
                }
                else {
                    root = rotateLeftRight(root);
                }
            }
        }
        return root;
    }

    void deletetheleaves(TreeNode* node)
    {
        if (node != nullptr) {
            deletetheleaves(node->left);
            deletetheleaves(node->right);
            delete node;
        }
    }

    void deletetheTree(TreeNode** root)
    {
        deletetheleaves(*root);
        *root = nullptr;
    }

/// public
public:
    Map() { theNode = nullptr; }
    ~Map() { deletetheTree(&theNode); }

    void insert(const string &name, int value,string process,Movie object)
    {
        if(process=="name") {
            theNode = thestringinsert(theNode, name,object);
        }
        else if (process=="number") {
            theNode = thenmumberinsert(theNode, value,object);
        }
    }

    void erase()
    {
        deletetheTree(&theNode);
    }

    vector<Movie> gettheTopMovies()
    {
        vector<Movie> TopMovies;
        TopMovies = inorderIDstorer(theNode);
        return TopMovies;
    }

};

class UnorderedMap
{
    int keys;
    list<Movie> *hashtable;

public:
    UnorderedMap(int number)
    {
        this->keys = number;
        hashtable = new list<Movie>[number];
    }

    void insertGenres(Movie object)
    {
        int index = hashGenre(object);
        if (index == -1) {
            return;
        }
        else {
            hashtable[index].push_back(object);
        }
    }

    int hashGenre(Movie object)
    {
        try {
            int index = object._genres.length();
            return (index % keys);
        }
        catch (const std::invalid_argument& ia) {
            return -1;
        }
    }

    void insertCompanies(Movie object)
    {
        int index = hashCompanies(object);
        if (index == -1) {
            return;
        }
        else {
            hashtable[index].push_back(object);
        }
    }

    int hashCompanies(Movie object)
    {
        try {
            int index = object._productionCompany.length();
            return (index % keys);
        }
        catch (const std::invalid_argument& ia) {
            return -1;
        }
    }

    void insertMovietiles(Movie object)
    {
        int index = hashTitles(object);
        if(index == -1){
            return;
        }
        else {
            hashtable[index].push_back(object);
        }
    }

    int hashTitles(Movie object)
    {
        try {
            int index = object._title.length();
            return (index % keys);
        }
        catch (const std::invalid_argument& ia) {
            return -1;
        }
    }

    bool titleexists(string name)
    {
        for (int i = 0; i < keys; i++) {
            for (auto x : hashtable[i])
                if (x._title=="") {
                    continue;
                } else if (x._title==name) {
                    return true;
                }
        }
        return false;
    }

    Movie getobject(string name)
    {
        Movie object;
        for (int i = 0; i < keys; i++) {
            for (auto x : hashtable[i])
                if (x._title=="") {
                    continue;
                } else if (x._title==name) {
                    object=x;
                    break;
                }
        }
        return object;
    }

    vector<Movie> getSameGenreMovies(string name,vector<Movie>& movies)
    {
        for (int i = 0; i < keys; i++) {
            for (auto x : hashtable[i])
                if(x._genres==name) {
                    movies.push_back(x);
                }
        }
        return movies;
    }

    vector<Movie> getSameCompanymovies(string name,vector<Movie>& movies)
    {
        for (int i = 0; i < keys; i++) {
            for (auto x : hashtable[i])
                if(x._productionCompany==name) {
                    movies.push_back(x);
                }
        }
        return movies;
    }
};

///=====================================================================================================================

class max_heap {
private:
    struct Node {
        int value;
        Movie Object;
    };
    vector<Node> heap_elements;

    int right_node(int rn)
    {
        int right_child = (2 + 2 * rn);
        return right_child;
    }

    int left_node(int ln)
    {
        int left_child = (1 + 2 * ln);
        return left_child;
    }

    int parent_node(int p)
    {
        int parent = (p - 1) / 2;
        return parent;
    }

    void heapify_u(int up)
    {
        /// First check if node and its parent heap properties
        Node object=heap_elements[up];
        int value=object.value;

        Node object2=heap_elements[parent_node(up)];
        int parentvalue=object.value;

        if (value > parentvalue && up) {
            /// swap if they violate the heap property
            swap(heap_elements[parent_node(up)], heap_elements[up]);
            /// now call heapify up lol
            heapify_u(parent_node(up));
        }
    }

/// public
public:
    void insert_key(Movie object)
    {
        Node node;
        /// First insert an element at the end of the tree/vector
        try {
            node.value=stoi(object._popularity);
            node.Object=object;
            heap_elements.push_back(node);
        }
            /// if stoi fails then just return
        catch (const std::invalid_argument& ia) {
            return;
        }
        /// Now get the element and call for the heapify up function
        int the_index = size_heap() - 1;
        heapify_u(the_index);
    }

    unsigned int size_heap()
    {
        int sh = heap_elements.size();
        return sh;
    }

    /// obtains the first 5 indices
    vector<Movie> top_five()
    {
        vector<Movie> movie_vector = {
                heap_elements[0].Object, heap_elements[1].Object, heap_elements[2].Object, heap_elements[3].Object, heap_elements[4].Object
        };
        return movie_vector;
    }

    vector<Movie> getelement(string company,string genre,string movietitle,vector<Movie> allmovies)
    {
        vector<Movie> relatedmovies;
        for (int i = 0; i < allmovies.size(); ++i) {
            if (allmovies[i]._title == movietitle){
                continue;
            }
            else if (allmovies[i]._productionCompany == company) {
                relatedmovies.push_back(allmovies[i]);
            }
            else if (allmovies[i]._genres == genre) {
                relatedmovies.push_back(allmovies[i]);
            }
        }
        return relatedmovies;
    }
};
