#pragma once
#include "MovieDefinitions.hpp"
#include "MovieDatabase.hpp"
#include "MovieFilter.hpp"
#include <string>
#include <vector>

class InputReader{
private:

public:
    std::vector<unsigned int> readAndSearch(const MovieDataBase& database, std::string input);
};