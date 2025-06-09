#pragma once

#include "Movies.hpp"
#include <string>
#include <vector>


class MovieDataBase{
private:
    std::vector <Movies> allMovies;
    
    Movies createMovie(std::string id, std::string titleType_mask, std::string primaryTitle, std::string originalTitle, std::string isAdult, std::string startYear, std::string endYear, std::string runtimeMinutes, std::string genres_mask);
    
public:
    MovieDataBase();

    void loadMoviesFromTXT(const std::string& filename);
};