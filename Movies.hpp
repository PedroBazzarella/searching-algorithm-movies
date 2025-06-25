#pragma once

#include <string>

class Movies{
private:
    int id;
    unsigned short titleType_mask;
    std::string primaryTitle;
    std::string originalTitle; 
    bool isAdult;
    unsigned short startYear;
    unsigned short endYear;
    unsigned int runtimeMinutes;
    unsigned int genres_mask;

    std::string getGenresAsString() const;
    std::string getTitleTypeAsString() const;

public:
    Movies(int id, unsigned short titleType_mask, std::string primaryTitle, std::string originalTitle, bool isAdult, unsigned short startYear, unsigned short endYear, int runtimeMinutes, unsigned int genres_mask);
    
    int getID ();
    unsigned short getTitleTypeMask();
    unsigned int getGenresMask();
    unsigned int getRuntimeMinutes();
    unsigned short getStartYear();

    std::string toString() const;
};


