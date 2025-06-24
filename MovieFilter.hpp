#pragma once

#include <vector>
#include <string>
#include "Movies.hpp"

struct Interval {int start; int end;};
enum movieFilterType{RELEASE_YEAR, MOVIE_GENRE, MOVIE_TYPE, DURATION, YEAR_INTERVAL};

class MovieFilter {
private:
    const MovieDataBase & database;

public:
    MovieFilter::MovieFilter(const MovieDataBase& database);

    std::vector<movieFilterType> filterTypes;
    std::vector<unsigned short> movieTypeMask;
    std::vector<unsigned int> movieGenreMask;
    std::vector<Interval> duration;
    int releaseYear;
    std::vector<Interval> yearInterval;

    std::vector<Movies> Filter(std::vector<Movies> movies) const;
    void addFilter(movieFilterType filter);
};