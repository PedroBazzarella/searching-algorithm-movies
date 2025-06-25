#pragma once

#include "Movies.hpp"
#include <string>
#include <vector>

class MovieDataBase{
private:
    std::vector <Movies> allMovies; //stores all movies
    std::vector <size_t> movieIndexTable; // stores index of a movie in the allMovies vector based on a hash formula

    //Sublists 
    std::vector <std::vector <size_t>> genreIndex; //list of genre vectors
    std::vector <unsigned int> genreIndexSize; //size of genre vectors
    std::vector <std::vector <size_t>> titleTypeIndex; //list of tittleType vectors
    std::vector <unsigned int> titleTypeIndexSize; //size of genre vectors
    std::vector <std::vector<unsigned int>> durationIndex; //movies ordered by duration in min
    std::vector <std::vector<unsigned int>> startYearIndex; //movies ordered by release year
    
    //aux functions
    size_t getBitPosition(unsigned int genreORtype_mask) const;
    void merge(std::vector <std::vector<unsigned int>>& array, int left, int mid, int right);
    void mergeSort(std::vector <std::vector<unsigned int>>& array, int left, int right);

    Movies createMovie(std::string id, std::string titleType_mask, std::string primaryTitle, std::string originalTitle, std::string isAdult, std::string startYear, std::string endYear, std::string runtimeMinutes, std::string genres_mask);
    
public:
    MovieDataBase();

    void loadMoviesFromTXT(const std::string& filename);
    Movies * findMovieByID(int id);
    const std::vector <size_t> & getGenreList(unsigned int genre_mask) const;
    const int getGenreListSize(unsigned int genre_mask) const;
    const std::vector <size_t> & getTitleTypeList(unsigned short titleType_mask) const;
    const int getTitleTypeListSize(unsigned short titleType_mask) const;
    const std::vector <std::vector<unsigned int>> & getDurationIndex() const;
    const std::vector <std::vector<unsigned int>> & getStartYearIndex() const;
    const int getStartYearPosition(unsigned short year) const;
};