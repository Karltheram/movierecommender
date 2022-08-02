#include <iostream>
#include <vector>
#include <string>
#include "Movie.h"
#include <chrono>

using namespace std::chrono;
using namespace std;
vector<Movie> getRecomendationsHeap(const Movie &object,vector<Movie> allmovies)
{
    vector<Movie> topFive;
    string movietitle = object._title;
    string moviecompany = object._productionCompany;
    string genre = object._genres;

    max_heap sort;
    topFive = sort.getelement(moviecompany, genre,movietitle,allmovies);
    for (int i = 0; i <  topFive.size(); ++i) {
        sort.insert_key(topFive[i]);
    }
    topFive = sort.top_five();
    int ranker=1;
    for (int i = 0; i <topFive.size(); i++) {
        cout<<ranker<< ": " << topFive[i]._title << endl;
        ranker++;
        if (ranker == 6){
            break;
        }
    }
    return topFive;
}

vector<Movie> getRecomendationsMap(const Movie &object, UnorderedMap SameCompanies, UnorderedMap SameGenres)
{
    string movietitle = object._title;
    string moviecompany = object._productionCompany;
    string genre = object._genres;
    vector<Movie> samecompanymovies;
    vector<Movie> samegenremovies;
    Map Reccomendations;
    samecompanymovies = SameCompanies.getSameCompanymovies(moviecompany, samecompanymovies);
    samegenremovies = SameGenres.getSameGenreMovies(genre, samegenremovies);

    /// Combine the vectors
    samecompanymovies.insert(samecompanymovies.end(), samegenremovies.begin(), samegenremovies.end());

    /// Now go through and find the most popular movies
    /// Get the popularity as key and the object as value
    for (int i=0; i < samecompanymovies.size(); i++) {
        if (samecompanymovies[i]._title == movietitle) {
            continue;
        }
        int popularityvalue = stoi(samecompanymovies[i]._popularity);
        Reccomendations.insert(samecompanymovies[i]._title, popularityvalue, "number", samecompanymovies[i]);
    }

    vector<Movie> inorder;
    inorder = Reccomendations.gettheTopMovies();
    vector<Movie> thetop;
    int ranker=1;
    for (int i = inorder.size()-1; i > 0; --i) {
        cout << ranker << ": " << inorder[i]._title << endl;
        thetop.push_back(inorder[i]);
        ranker++;
        if (ranker == 6) {
            break;
        }
    }
    Reccomendations.erase();
    return thetop;
}

int main()
{
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds> (stop - start);
    Movie manager;
    manager.fileReader("movies.csv");
    vector<Movie> allmovies = manager.rolodex;

    /// insert Movie Companies,Genres, and Movie Titles as keys with
    /// movies as values with chaining into the hash table
    UnorderedMap SameGenres(1000);
    UnorderedMap SameCompanies(1000);
    UnorderedMap Movietitles(1000);

    /// The map to sort the order with the vector to store the top 5
    Map ReccomendationsAlgorithm;

    /// The vector that will contain the reccomendations
    vector<Movie> TheRecommendations;

    /// Create the Unordered Maps
    for (int i = 0; i < allmovies.size(); i++) {
        SameGenres.insertGenres(allmovies[i]);
        SameCompanies.insertCompanies(allmovies[i]);
        Movietitles.insertMovietiles(allmovies[i]);
    }

    /// The User Interface
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "Welcome to the Movie Recommender!" << endl;
    cout << "Our recommender works on a criteria:" << endl;
    cout << "The movie with the highest popularity in "
            "the same genre and movie studio is the priority." << endl;
    cout << "If there are no other movies in the movie studio then"
            "the movie in the same genre will go next."<< endl;

    /// The loop for the user Interface if the user wants to keep going
    while (true) {
        int menuselection = 0;
        string movietitle;
        Movie themovie;
        cin.clear();
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "What movie do you want to search?" << endl;
        getline(cin, movietitle);
        if (movietitle.empty()) {
            getline(cin, movietitle);
        }

        /// Input error check
        while (true) {
            if (!(Movietitles.titleexists(movietitle))) {
                cin.clear();
                cin.ignore(100, '\n');
            }
            else {
                if (Movietitles.titleexists(movietitle)) {
                    start = high_resolution_clock::now();
                    themovie = Movietitles.getobject(movietitle);
                    break;
                }
            }
            cout << "Cannot find the movie" << endl;
            cout << "Please type the movie title correctly" << endl;
            getline(cin, movietitle);
        }

        cin.clear();
        cout << endl;
        manager.prinObject(themovie);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        cout << "The finding and printing the movie took: "
             << duration.count() << " microseconds!" << endl << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "What algorithm do you want to work with to find your top 5 recommendations?" << endl;
        cout << "1. Heapsort" << endl;
        cout << "2. Maps" << endl;
        cout << "Please enter the number" << endl;
        cin >> menuselection;

        while (true) {
            if (!cin) {
                cin.clear();
                cin.ignore(100, '\n');
            }
            else if (menuselection == 1) {
                cout << "Here are your TOP 5 Recommendations" << endl;
                start = high_resolution_clock::now();
                TheRecommendations = getRecomendationsHeap(themovie, allmovies);
                break;
            }
            else if (menuselection == 2) {
                cout << "Here are your TOP 5 Recommendations" << endl;
                start = high_resolution_clock::now();
                TheRecommendations = getRecomendationsMap(themovie, SameCompanies, SameGenres);
                break;
            }
            cout << "Wrong Input" << endl;
            cout << "Please enter the number again" << endl;
            cin >> menuselection;
        }

        cin.clear();
        cout << endl;
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds> (stop - start);

        cout << "Finding recommendations took: "
             << duration.count() << " microseconds!" << endl << endl;
        cout << "-------------------------------------------------------------------------------" << endl;

        /// Learn more about a movie recommended to you
        int menuselector2;
        int counter = 1;
        cout << "If you want to learn more about movies we recommended to you, please type the number associated to the movie" << endl;
        cout << "If you want to stop the Movie Recommender, please type 6 to exit" << endl;
        cout << "Search again press 0" << endl;

        cin >> menuselector2;
        while (true) {
            if (!cin) {
                cin.clear();
                cin.ignore(100, '\n');
            }
            else if (menuselector2 == 6) {
                exit(1);
            }
            else if (menuselector2 == 0) {
                break;
            }
            else {
                for (int i=0; i < TheRecommendations.size(); i++) {
                    if (menuselector2 == counter) {
                        start = high_resolution_clock::now();
                        manager.prinObject(TheRecommendations[i]);
                        break;
                    }
                    counter++;
                }
                break;
            }
            cout << "Wrong Input" << endl;
            cout << "Please enter the number again" << endl;
            cin >> menuselector2;
        }
        if (menuselector2 != 0){
            cin.clear();
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);

            cout << "Printing the movie took: "<< duration.count() << " microseconds!" << endl <<endl;
            cout << "-------------------------------------------------------------------------------" << endl;

            /// Loop again to continue exploring our recommendations
            cout << "If you would like to use the movie recommender again or exit the program completely please type 0 or 1" << endl;
            int menuselector3;
            cin >> menuselector3;
            while (true) {
                if (!cin) {
                    cin.clear();
                    cin.ignore(100, '\n');
                }
                else if (menuselector3 == 0) {
                    break;
                }
                else if (menuselector3 == 1) {
                    exit(1);
                }
                cout << "Wrong Input" << endl;
                cout << "Please enter the number again" << endl;
                cin >> menuselector3;
            }
        }
        cin.clear();
        TheRecommendations.clear();
        ReccomendationsAlgorithm.erase();
    }
}
