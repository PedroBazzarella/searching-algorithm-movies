#include "Movies.hpp"
#include "Movie_Definitions.hpp"
#include <sstream>
#include <string>
#include <vector>

Movies::Movies(int id, unsigned short titleType_mask, std::string primaryTitle, std::string originalTitle, bool isAdult, int startYear, int endYear, int runtimeMinutes, unsigned int genres_mask){
    this->id = id;
    this->titleType_mask = titleType_mask;
    this->primaryTitle = primaryTitle;
    this->originalTitle = originalTitle;
    this->isAdult = isAdult;
    this->startYear = startYear;
    this->endYear = endYear;
    this->runtimeMinutes = runtimeMinutes;
    this->genres_mask = genres_mask;
}


std::string Movies::getGenresAsString() const{
    std::vector <std::string> genresList;

    for (const auto & pair : genresMap){ // pair stores key + value for each genre in genresMap
        unsigned int thisGenreMask = pair.first; // gets genre key/ activated bit
        std::string const & genreName = pair.second; // gets genre value/name

        if ((this->genres_mask & thisGenreMask) != 0){
            genresList.push_back (genreName); //stores genre name 
        }
    }

    if (genresList.empty()){ 
        genresList.push_back("N/A");
    }

    std::string movieGenres = "";

    for (unsigned i = 0; i < genresList.size(); i++){ 
        movieGenres += genresList[i];

        if (i < genresList.size() - 1)
            movieGenres += ", ";
    }
    
    return movieGenres; 
}


std::string Movies::getTitleTypeAsString() const{
    std::string movieType = "";

    for(const auto & pair : titleTypesMap){ // pair stores key + value for each title type in titleTypesMap
        unsigned short titleTypeMask = pair.first;
        std::string const & titleTypeName = pair.second;
        
        if (this->titleType_mask == titleTypeMask){
            movieType = titleTypeName;
            break;
        }
    }

    if (movieType == "")
        movieType = "N/A";

    return movieType;
}


std::string Movies::toString() const{
    std::ostringstream movieData;


    movieData << "tt" << id << " " << getTitleTypeAsString() << " " << originalTitle << " " << startYear << " "<< endYear << " " << getGenresAsString();

    return movieData.str();
}