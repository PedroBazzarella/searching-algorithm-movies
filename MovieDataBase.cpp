#include "MovieDataBase.hpp"
#include "Movie_Definitions.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>

MovieDataBase::MovieDataBase(){};

Movies MovieDataBase::createMovie(std::string id_string, std::string titleType_string, std::string primaryTitle_string, std::string originalTitle_string, std::string isAdult_string, std::string startYear_string, std::string endYear_string, std::string runtimeMinutes_string, std::string genres_string){

    // TYPE CONVERSIONS ----------------------------------------

    //convert id_string to int
    std::string numID = id_string.substr(2); //tt00000 -> id begins at third index (2)
    int id = std::stoi(numID); 

    //convert isAsult_string to bool
    bool isAdult = std::stoi(isAdult_string); 

    //convert startYear_string to int if the value is valid, else default to 0
    int startYear = (startYear_string == "\\N") ? 0 : std::stoi(startYear_string);

    //convert endYear_string to int if the value is valid, else default to 0
    int endYear = (endYear_string == "\\N") ? 0 : std::stoi(endYear_string);

    //convert runtimeMinutes_string to int if the value is valid, else default to 0
    int runtimeMinutes = (runtimeMinutes_string == "\\N") ? 0 : std::stoi(runtimeMinutes_string);

    // END TYPE CONVERSIONS ------------------------------------

    // MASKS CREATION -------------------------------------------

    unsigned short titleType_mask = 0;

    if (stringToTitleTypeMask.count(titleType_string)) //searches on the titleTypesMap for the key/type 
        titleType_mask = stringToTitleTypeMask.at(titleType_string); //returns value/titleType mask

    unsigned int genre_mask = 0;

    std::stringstream genreNames(genres_string); // creates stream for genres_string
    std::string singleGenre;

    while (std::getline(genreNames, singleGenre, ',')){ //gets all genres
        if(stringToGenreMask.count(singleGenre)){ //searches key/genre name
            genre_mask |= stringToGenreMask.at(singleGenre); //returns value/genre mask
        }
    }
    
    return Movies(id, titleType_mask, primaryTitle_string, originalTitle_string, isAdult, startYear, endYear, runtimeMinutes, genre_mask);
    
}


void MovieDataBase::loadMoviesFromTXT(const std::string & filename){
    auto start_time = std::chrono::high_resolution_clock::now();

    std::ifstream inputFile(filename); // tries to open file

    if (inputFile.is_open() == false){
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line; // stores each line

    std::getline(inputFile, line); // skips header line

    while (std::getline(inputFile, line)){
        std::stringstream stringLine(line); // creates stream from line
        std::string field; 

        // GETTING DATA FROM FILE ----------------------------------
        //extracting fields as string, values separated by TAB 

        //Id tt0000000
        std::getline(stringLine, field, '\t'); 
        std::string id_string = field;

        //titleType
        std::getline(stringLine, field, '\t'); 
        std::string titleType_string = field;

        //primaryTitle
        std::getline(stringLine, field, '\t'); 
        std::string primaryTitle_string = field;

        //originalTitle
        std::getline(stringLine, field, '\t'); 
        std::string originalTitle_string = field;

        //isAdult
        std::getline(stringLine, field, '\t'); 
        std::string isAdult_string = field;

        //startYear
        std::getline(stringLine, field, '\t'); 
        std::string startYear_string = field;

        //endYear
        std::getline(stringLine, field, '\t'); 
        std::string endYear_string = field;

        //runtimeMinutes
        std::getline(stringLine, field, '\t'); 
        std::string runtimeMinutes_string = field;


        //genres
        std::getline(stringLine, field, '\t'); 
        std::string genres_string = field;

        // END GETTING DATA FROM FILE ------------------------------

        // CREATING OBJECT -----------------------------------------
        Movies movie = createMovie(id_string, titleType_string, primaryTitle_string, originalTitle_string, isAdult_string, startYear_string, endYear_string, runtimeMinutes_string, genres_string);

        allMovies.push_back(movie);

        // HASH -----------------------------------------
        std::cout << movie.toString() << std::endl;
        /*
        LINHA 
        DE
        TESTE
        ACIMA
        */
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_raw = end_time - start_time;
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration_raw);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "FINISHED LOADING DATABASE: " << duration_ms.count() << " milliseconds." << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

}