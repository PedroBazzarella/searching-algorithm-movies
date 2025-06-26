#pragma once

#include <vector>
#include <string>
#include "Movies.hpp"
#include "MovieDatabase.hpp"

struct Interval {int start; int end;};
enum movieFilterType{RELEASE_YEAR, MOVIE_GENRE, MOVIE_TYPE, DURATION, YEAR_INTERVAL};

class MovieFilter {
private:
    const MovieDataBase & database;

public:
    MovieFilter(const MovieDataBase& database);

    std::vector<movieFilterType> filterTypes;
    unsigned short movieTypeMask;
    unsigned int movieGenreMask;
    Interval duration;
    unsigned short releaseYear;
    Interval yearInterval;

    std::vector<unsigned int> Filter();
    void addFilter(movieFilterType filter);
};