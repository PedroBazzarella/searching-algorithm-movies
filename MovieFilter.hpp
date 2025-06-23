#pragma once

#include <vector>
#include <string>
#include "Movies.hpp"

class MovieFilter {
private:

public:
    struct YearInterval {int start; int end;};

    std::vector<unsigned int> movieTypeMask;
    std::vector<unsigned int> movieGenreMask;
    std::vector<int> duration;
    std::vector<int> releaseYear;
    std::vector<YearInterval> yearInterval;

    std::vector<Movies> Filter() const;
};