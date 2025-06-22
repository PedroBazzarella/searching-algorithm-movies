#pragma once

#include <string>

class Movies{
private:
    int id;
    unsigned short titleType_mask;
    std::string primaryTitle;
    std::string originalTitle; 
    bool isAdult;
    int startYear;
    int endYear;
    int runtimeMinutes;
    unsigned int genres_mask;

    std::string getGenresAsString() const;
    std::string getTitleTypeAsString() const;

public:
    Movies(int id, unsigned short titleType_mask, std::string primaryTitle, std::string originalTitle, bool isAdult, int startYear, int endYear, int runtimeMinutes, unsigned int genres_mask);
    
    int getID ();

    std::string toString() const;
};


