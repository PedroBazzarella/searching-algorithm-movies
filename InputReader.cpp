#include "InputReader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

/*
    Example: g.action,g.adventure,d.60.120+g.horror,y.1999,t.movie
    Use ',' to add AND operator
    Use '+' to add OR operator
*/

std::vector<unsigned int> InputReader::readAndSearch(const MovieDataBase& database, std::string input){
    std::vector<unsigned int> result = {};
    std::vector<MovieFilter> filters = {};
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
}