#include "Movies.hpp"
#include "MovieDefinitions.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

Movies::Movies(int id, unsigned short titleType_mask, std::string primaryTitle, std::string originalTitle, bool isAdult, unsigned short startYear, unsigned short endYear, int runtimeMinutes, unsigned int genres_mask){
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

int Movies::getID(){
    return id;
}

unsigned short Movies::getTitleTypeMask(){
    return titleType_mask;
}

unsigned int Movies::getGenresMask(){
    return genres_mask;
}

unsigned int Movies::getRuntimeMinutes(){
    return runtimeMinutes;
}

unsigned short Movies::getStartYear(){
    return startYear;
};

std::string Movies::getGenresAsString() const{
    std::string movieGenres = "";
    
    for(int i = 0; i < GenresNameList.size(); ++i){
        if((1u << i & genres_mask) != 0){
            if(movieGenres != "") movieGenres.append(",");
            movieGenres.append(GenresNameList[i]);
        }
    }
    if (movieGenres.empty()) return "N/A";
    return movieGenres;
}


std::string Movies::getTitleTypeAsString() const{
    for(int i = 0; i < 31; ++i){
        if((1 << i) & genres_mask != 0){
            return TypesNameList[i];
        }
    }
    
    return "N/A";
}


std::string Movies::toString() const{
    std::ostringstream movieData;

    movieData << "tt" << id << " " << getTitleTypeAsString() << " " << originalTitle << " " << startYear << " "<< endYear << " " << getGenresAsString();

    return movieData.str();
}