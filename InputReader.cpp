#include "InputReader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

/*
<<<<<<< HEAD
    Example: g.action,g.adventure,d.60.120+g.horror,y.1999,t.movie
    Use ',' to add AND operator
    Use '+' to add OR operator
=======
    Example: g.Action,g.Adventure,d.60.120+g.Horror,y.1999,t.movie
    Use ',' to add AND operator
    Use '+' to add OR operator
    g - movie genre
    t - movie type
    y - release year
    d.x.y - duration in minutes from x to y
>>>>>>> pedro
*/

std::vector<unsigned int> InputReader::readAndSearch(const MovieDataBase& database, std::string input){
    std::vector<unsigned int> result = {};
    std::vector<MovieFilter> filters = {};
<<<<<<< HEAD
=======
    std::vector<bool> checkMovie(IndexConfig::INDEX_SIZE, false);

>>>>>>> pedro
    /*
        Split OR
    */
    std::stringstream stringOr(input);
    std::vector<std::string> parsedOr;
    std::string token;
    while (std::getline(stringOr, token, '+')) {
        parsedOr.push_back(token);
    }

    /*
        Split AND
    */
    for(std::string filter : parsedOr){
        std::stringstream stringAnd(filter);
        std::vector<std::string> parsedAnd;
<<<<<<< HEAD

        while (std::getline(stringAnd, token, ',')) {
            MovieFilter newFilter(database);
            /*
                Add filters to Filter
            */
           parsedAnd.push_back(token);
        }

        for(std::string stringFilter : parsedAnd){
            
        }
    }
=======
        MovieFilter newFilter(database);

        while (std::getline(stringAnd, token, ',')) {
            /*
                Parse filters
            */
            parsedAnd.push_back(token);
        }

        for(std::string stringF : parsedAnd){
            std::stringstream stringFilter(stringF);
            std::vector<std::string> parsedFilter;

            while (std::getline(stringFilter, token, '.')) {
                /*
                    Add filters to Filter
                */
               parsedFilter.push_back(token);
            }

            if(parsedFilter[0] == "g"){
                newFilter.addFilter(MOVIE_GENRE);
                newFilter.movieGenreMask |= genreFromString(parsedFilter[1]);
            }else if(parsedFilter[0] == "t"){
                newFilter.addFilter(MOVIE_TYPE);
                newFilter.movieTypeMask = typeFromString(parsedFilter[1]);
            }else if(parsedFilter[0] == "y"){
                newFilter.addFilter(RELEASE_YEAR);
                newFilter.releaseYear = stoi(parsedFilter[1]);
            }else if(parsedFilter[0] == "d"){
                newFilter.addFilter(DURATION);
                newFilter.duration.start = stoi(parsedFilter[1]);
                newFilter.duration.end = stoi(parsedFilter[2]);
            }
        }

        filters.push_back(newFilter);
    }

    for(MovieFilter filter : filters){
        std::vector<unsigned int> halfResults = filter.Filter();
        std::cout << filter.toString() << std::endl;
        for(unsigned int movieID : halfResults){
            if(!checkMovie[movieID]){
                checkMovie[movieID] = true;
                result.push_back(movieID);
            }
        }
    }

    return result;
>>>>>>> pedro
}