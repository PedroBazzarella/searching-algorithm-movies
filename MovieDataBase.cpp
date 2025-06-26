#include "MovieDataBase.hpp"
#include "MovieDefinitions.hpp"
#include "MovieFilter.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <cmath>

MovieDataBase::MovieDataBase(bool debug_mode)
{
    this->debug_mode = debug_mode;

    // initializes hash table with predefined size and fills all slots with null
    movieIndexTable.resize(IndexConfig::INDEX_SIZE, IndexConfig::NULL_INDEX);

    // creates 27 empty lists, one for each genre
    genreIndex.resize(IndexConfig::NUM_GENRES);
    genreIndexSize.resize(IndexConfig::NUM_GENRES);
    for(int i : genreIndexSize) i = 0;

    // creates 10 empty lists, one for each tittle type
    titleTypeIndex.resize(IndexConfig::NUM_TITTLE_TYPES);
    titleTypeIndexSize.resize(IndexConfig::NUM_TITTLE_TYPES);
    for(int i : titleTypeIndexSize) i = 0;

    // static vector for movie ids by duration time
    durationIndex.resize(52000);

    // static vector for movie ids by release year
    startYearIndex.resize(2030);
}

Movies MovieDataBase::createMovie(std::string id_string, std::string titleType_string, std::string primaryTitle_string, std::string originalTitle_string, std::string isAdult_string, std::string startYear_string, std::string endYear_string, std::string runtimeMinutes_string, std::string genres_string)
{

    // TYPE CONVERSIONS ----------------------------------------

    // convert id_string to int
    std::string numID = id_string.substr(2); // tt00000 -> id begins at third index (2)
    int id = std::stoi(numID);

    // convert isAsult_string to bool
    bool isAdult = std::stoi(isAdult_string);

    // convert startYear_string to int if the value is valid, else default to 0
    unsigned short startYear = (startYear_string == "\\N") ? 0 : std::stoi(startYear_string);

    // convert endYear_string to int if the value is valid, else default to 0
    unsigned short endYear = (endYear_string == "\\N") ? 0 : std::stoi(endYear_string);

    // convert runtimeMinutes_string to int if the value is valid, else default to 0
    unsigned int runtimeMinutes = (runtimeMinutes_string == "\\N") ? 0 : std::stoi(runtimeMinutes_string);

    // END TYPE CONVERSIONS ------------------------------------

    // MASKS CREATION -------------------------------------------

    unsigned short titleType_mask = typeFromString(titleType_string);

    unsigned int genre_mask = 0;

    std::stringstream genreNames(genres_string); // creates stream for genres_string
    std::string singleGenre;

    while (std::getline(genreNames, singleGenre, ',')){ // gets all genres from stream
        genre_mask |= genreFromString(singleGenre); // add genre bitmask to movie
    }

    return Movies(id, titleType_mask, primaryTitle_string, originalTitle_string, isAdult, startYear, endYear, runtimeMinutes, genre_mask);
}

void MovieDataBase::loadMoviesFromTXT(const std::string &filename)
{
    auto start_time = std::chrono::high_resolution_clock::now();

    std::ifstream inputFile(filename); // tries to open file

    if (inputFile.is_open() == false)
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line; // stores each line

    std::getline(inputFile, line); // skips header line

    while (std::getline(inputFile, line))
    {
        if(line.empty()) continue;
        std::stringstream stringLine(line); // creates stream from line
        std::string field;

        // GETTING DATA FROM FILE ----------------------------------
        // extracting fields as string, values separated by TAB

        // Id tt0000000
        std::getline(stringLine, field, '\t');
        std::string id_string = field;

        // titleType
        std::getline(stringLine, field, '\t');
        std::string titleType_string = field;

        // primaryTitle
        std::getline(stringLine, field, '\t');
        std::string primaryTitle_string = field;

        // originalTitle
        std::getline(stringLine, field, '\t');
        std::string originalTitle_string = field;

        // isAdult
        std::getline(stringLine, field, '\t');
        std::string isAdult_string = field;

        // startYear
        std::getline(stringLine, field, '\t');
        std::string startYear_string = field;

        // endYear
        std::getline(stringLine, field, '\t');
        std::string endYear_string = field;

        // runtimeMinutes
        std::getline(stringLine, field, '\t');
        std::string runtimeMinutes_string = field;

        // genres
        std::getline(stringLine, field, '\t');
        std::string genres_string = field;

        // END GETTING DATA FROM FILE ------------------------------

        // CREATING OBJECT -----------------------------------------
        Movies movie = createMovie(id_string, titleType_string, primaryTitle_string, originalTitle_string, isAdult_string, startYear_string, endYear_string, runtimeMinutes_string, genres_string);

        allMovies.push_back(movie);

        // HASH -----------------------------------------

        size_t storageIndexInAllMovies = allMovies.size() - 1;

        // calculates perfect hash index
        size_t hashIndex = (movie.getID() - IndexConfig::ID_OFFSET) / 2;

        movieIndexTable[hashIndex] = storageIndexInAllMovies;

        if(debug_mode){
            std::cout << movie.toString() << std::endl;
        }
        /*
        LINHA
        DE
        TESTE
        ACIMA
        */

        // END HASH -----------------------------------------

        // SUBLISTS -----------------------------------------
        unsigned short titleTypeMask = movie.getTitleTypeMask();
        if (titleTypeMask > 0)
        {
            size_t whichTypeIndex = getBitPosition(titleTypeMask);
            if (whichTypeIndex < titleTypeIndex.size())
            {
                titleTypeIndex[whichTypeIndex].push_back(movie.getID()); // puts the movie id in the list of its tittleType
                titleTypeIndexSize[whichTypeIndex]++;
            }
        }

        unsigned int genreMask = movie.getGenresMask();

        if (genreMask > 0)
        {
            for (unsigned i = 0; i < IndexConfig::NUM_GENRES; i++)
            {                                        // checking all genres
                unsigned int eachGenreMask = 1 << i; // generates mask for each genre

                if ((eachGenreMask & genreMask) != 0)
                {
                    genreIndex[i].push_back(movie.getID()); // puts the movie id in the list of its genre
                    genreIndexSize[i]++;
                }
            }
        }
        //duration list
        durationIndex[movie.getRuntimeMinutes()].push_back(movie.getID());

        //startYear list
        //std::cout << getStartYearPosition(movie.getStartYear()) << std::endl;
        startYearIndex[movie.getStartYear()].push_back(movie.getID());

        // END SUBLISTS -------------------------------------
    }

    //ordering duration list
    //mergeSort(durationIndex, 0, durationIndex.size() - 1);

    //calculating time spent
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_raw = end_time - start_time;
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration_raw);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "FINISHED LOADING DATABASE: " << duration_ms.count() << " milliseconds." << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
}

const Movies* MovieDataBase::findMovieByID(int id) const{
    size_t hashIndex = (id - IndexConfig::ID_OFFSET) / 2;

    if (hashIndex > movieIndexTable.size() - 1)
    {
        return nullptr; // id out of our range
    }

    size_t storageIndexInAllMovies = movieIndexTable[hashIndex];

    if (storageIndexInAllMovies != IndexConfig::NULL_INDEX)
    {
        return &allMovies[storageIndexInAllMovies]; // returns movie obj
    }

    return nullptr;
}

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
const std::vector<size_t> &MovieDataBase::getGenreList(unsigned int genre_mask){
=======
const std::vector<size_t> &MovieDataBase::getGenreList(unsigned int genre_mask) const{
>>>>>>> pedro
=======
const std::vector<size_t> &MovieDataBase::getGenreList(unsigned int genre_mask) const{
>>>>>>> pedro
=======
const std::vector<size_t> &MovieDataBase::getGenreList(unsigned int genre_mask) const{
>>>>>>> pedro
    size_t whichGenre = getBitPosition(genre_mask);

    return genreIndex.at(whichGenre); // returns list of asked genre
}

const int MovieDataBase::getGenreListSize(unsigned int genre_mask) const{
    size_t whichGenre = getBitPosition(genre_mask);

    return genreIndexSize.at(whichGenre); // returns size of asked genre
}

const std::vector <size_t> & MovieDataBase::getTitleTypeList(unsigned short titleType_mask) const{
    size_t whichType = getBitPosition(titleType_mask);

    return titleTypeIndex.at(whichType); // returns list of asked type
}

const int MovieDataBase::getTitleTypeListSize(unsigned short titleType_mask) const{
<<<<<<< HEAD
<<<<<<< HEAD
    size_t whichGenre = getTitleTypeListSize(titleType_mask);
=======
    size_t whichGenre = getBitPosition(titleType_mask);
>>>>>>> pedro
=======
    size_t whichGenre = getBitPosition(titleType_mask);
>>>>>>> pedro

    return titleTypeIndexSize.at(whichGenre); // returns size of asked genre
}

const std::vector <std::vector<unsigned int>> & MovieDataBase::getDurationIndex() const{
    return durationIndex;
}

const std::vector <std::vector<unsigned int>> & MovieDataBase::getStartYearIndex() const{
    return startYearIndex;
}

const int MovieDataBase::getStartYearPosition(unsigned short year) const{
<<<<<<< HEAD
<<<<<<< HEAD
    return year+500-2025;
=======
    return (year-2025+499 < 0) ? 0 : year-2025+499;
>>>>>>> pedro
=======
    return (year-2025+499 < 0) ? 0 : year-2025+499;
>>>>>>> pedro
}


//AUX FUNCTIONS

size_t MovieDataBase::getBitPosition(unsigned int genreORtype_mask) const
{
    if (genreORtype_mask == 0)
        return 0;

    unsigned int pos = log2(genreORtype_mask);

    return static_cast<size_t>(pos);
}

/*
void MovieDataBase::merge(std::vector<unsigned int>& array, int left, int mid, int right){

    //calculates both halfs
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;

    //temporary vectors
    std::vector<unsigned int> leftArray(sizeLeft);
    std::vector<unsigned int> rightArray(sizeRight);

    //copy paste to temporary vectors
    for (int i = 0; i < sizeLeft; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < sizeRight; j++)
        rightArray[j] = array[mid + 1 + j];

    // --- merge process ---
    int i = 0; // initial index of leftArray
    int j = 0; // initial index of rightArray
    int k = left; // initial index of the original array 

    // compares elements of left and right arrays and stores the lowest in the original array
    while (i < sizeLeft && j < sizeRight) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // if exists any left elements in leftArray, copy them to array
    while (i < sizeLeft) {
        array[k] = leftArray[i];
        i++;
        k++;
    }

    // if exists any left elements in rightArray, copy them to array
    while (j < sizeRight) {
        array[k] = rightArray[j];
        j++;
        k++;
    }
}


void MovieDataBase::mergeSort(std::vector<unsigned int>& array, int left, int right){
    // if subarray has 1 or 0 elements, its ordered 
    if (left >= right) {
        return;
    }

    // dividing array into two
    int mid = left + (right - left) / 2;

    // calls mergeSort for first half
    mergeSort(array, left, mid);

    // calls mergeSort for second half
    mergeSort(array, mid + 1, right);

    // merges both ordered halfs
    merge(array, left, mid, right);
}*/