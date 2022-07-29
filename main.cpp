#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

using namespace std;
class Movie {
private:
    string _id;
    string _title;
    vector<string> _genres;
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

public:
    vector<Movie> rolodex;
    Movie() {};

    Movie(string id, string title, vector<string> genres, string originalLanguage, string overview, string popularity, string productionCompany, string releaseDate,
          string budget, string revenue, string runTime, string status, string tagline, string voteAverage, string voteCount, string poster, string backdrop)
    {
        _id = id;
        _title = title;
        _genres = genres;
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

    void fileReader(string dataset)
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

            /// need to convert to
            int id;
            float popularity;
            int budget;
            int revenue;
            int runtime;
            float voteAverage;
            int voteCount;

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

                /// list of genres per title
                vector<string> genres;
                stringstream ss(genre);
                while (ss.good()) {
                    string substr;
                    getline(ss,substr, '-');
                    genres.push_back(substr);
                }

                /// conversions from string to other
                /*id = stoi(temp_id);
                popularity = stof(temp_popularity);
                budget = stoi(temp_budget);
                revenue = stoi(temp_revenue);
                runtime = stoi(temp_runtime);
                voteAverage = stof(temp_voteAverage);
                voteCount = stoi(temp_voteCount);*/

                Movie bundle(temp_id, title, genres, originalLanguage, overview, temp_popularity, productionCompany, releaseDate,
                             temp_budget, temp_revenue, temp_runtime, status, tagline, temp_voteAverage, temp_voteCount, poster, backdrop);
                rolodex.push_back(bundle);
                movieCount++;
            }
        }
    }

    void print() {
        int count = 0;
        int ticker = 2;
        for (int i = 0; i < rolodex.size(); ++i) {
            cout << "Movie - " << rolodex[i]._title << " (ID: " << rolodex[i]._id << ")" << endl << "Runtime: (" << rolodex[i]._runTime << " minutes)" << endl;
            cout << "Genres: ";
            int counter = 0;
            for (int j = 0; j < rolodex[i]._genres.size(); ++j) {
                if (counter != rolodex[i]._genres.size() - 1)
                    cout << rolodex[i]._genres[j] << "-";
                else
                    cout << rolodex[i]._genres[j];
                counter++;
            }
            cout << endl << "\nTagline: " << rolodex[i]._tagline << endl;
            cout << "Language (" << rolodex[i]._originalLanguage << "), " << "Released (" << rolodex[i]._releaseDate << "), " << "Budget: " << rolodex[i]._budget << " Revenue: " << rolodex[i]._revenue << endl;
            cout << "Popularity of Movie: " << rolodex[i]._popularity << " is based on " << rolodex[i]._voteAverage << " voting average from " << rolodex[i]._voteCount << " voters!" << endl;
            cout << "\n" << ticker << endl;
            cout << "-------------------------------------------------------------------------------" << endl;

            count++;
            ticker++;
            if (count == 100)
                break;
        }
    }

};

int main()
{
    Movie manager;
    manager.fileReader("movies.csv");

    int menuselection;
    string movietitle;
    cout<< "Welcome to the Movie Recommender!" <<endl;
    cout<< "What movie do you want to have reccomendations with?" <<endl;
    getline(cin,movietitle);
    std::for_each(movietitle.begin(), movietitle.end(), [](char & c) {
        c = ::tolower(c);
    });
    //go look for this movie top 3 similar results by name first then recent release date
    //if its not the 3 movies prompt to ask again

    cout<<movietitle<<endl;
    cout<< "What algorithm do you want to work with?" <<endl;
    cout << "1. B+ Tree" <<endl;
    cout << "2. Maps"<<endl;
    cout << "Please enter the number"<<endl;
    cin >> menuselection;
    while(true){
        if (!cin){
            cin.clear();
            cin.ignore(100, '\n');
        }
        cout << "Wrong Input"<<endl;
        cout << "Please enter the number again"<<endl;
        cin >> menuselection;
        if (menuselection == 1){
            break;
        }else if (menuselection==2){
            break;
        }
    }

    switch (menuselection) {
        case 1:
            //calls the function
            break;
        case 2:
            //calls the function
            break;
    }


    return 0;
}