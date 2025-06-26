#include "MovieFilter.hpp"
#include "MovieDatabase.hpp"
#include <iostream>

MovieFilter::MovieFilter(const MovieDataBase& database) : database(database) {}

/* 
    Add filterType to filter in correct priority
*/
void MovieFilter::addFilter(movieFilterType filter){
    if(filterTypes.size() == 0){
        filterTypes.push_back(filter);
        return;
    }
    for(int i = 0; i < filterTypes.size(); ++i){
        if(filterTypes[i] > filter){
            filterTypes.insert(filterTypes.begin() + i, filter);
            return;
        }
    }
    filterTypes.push_back(filter);
}

/*
    Filter the movies, this function acts as an AND operator
    result carries the IDs of the movies that matches the filter 
*/
std::vector<unsigned int> MovieFilter::Filter(){
    std::vector<unsigned int> result = {}; // movies IDs
    
    /*
        Start result list
    */
    switch(filterTypes[0]){
        case MOVIE_TYPE:{
            /*
                Get smaller movie type list
            */
            std::vector<size_t> initialList = database.getTitleTypeList(movieTypeMask);
            result.assign(initialList.begin(), initialList.end());
            break;
        }
        case MOVIE_GENRE:{
            /*
                Get smaller movie genre list
            */
            int bestMovieList = -1;
            for(int i = 0; i < 31; ++i){
                if(((1 << i) & movieGenreMask) != 0){
                    if(bestMovieList == -1 || database.getGenreListSize(1 << i) < database.getGenreListSize(1 << bestMovieList)){
                        bestMovieList = i;
                    }
                }
            }
            std::vector<size_t> initialList = database.getGenreList(1 << bestMovieList);
            result.assign(initialList.begin(), initialList.end());
            break;
        }
        case DURATION:{
            /*
                Get movies with duration between range
            */
            std::vector<std::vector<unsigned int>> initialList = database.getDurationIndex();
            for(int i = duration.start; i <= duration.end; ++i){
                for(unsigned int movieID : initialList[i]){
                    result.push_back(movieID);
                }
            }
            break;
        }
        case RELEASE_YEAR:{
            /*
                Get movies by a specific release year
            */
            std::vector<unsigned int> initialList = database.getStartYearIndex()[releaseYear];
            result.assign(initialList.begin(), initialList.end());
            break;
        }
        case YEAR_INTERVAL:{

            break;
        }
    }

    /*
        Already filtered the by the first parameter 
    */
    filterTypes.erase(filterTypes.begin());

    if(!filterTypes.empty()){
        for (int i = int(result.size()) - 1; i >= 0; --i) {
            unsigned int movieID = result[i];
            const Movies * movie = database.findMovieByID(movieID);
            bool keepMovie = true;
            for(movieFilterType filter : filterTypes){
                switch(filter){
                    case MOVIE_TYPE:{
                        unsigned short movieMask = movie->getTitleTypeMask();
                        if((movieTypeMask & movieMask) == 0){
                            result.erase(result.begin() + i);
                            keepMovie = false;
                            break;
                        }else{
                        }
                        break;
                    }
                    case MOVIE_GENRE:{
                        unsigned int movieMask = movie->getGenresMask();
                        for(unsigned int j = 0; j < 31; ++j){
                            if((1 << j & movieGenreMask) != 0 && (1 << j & movieMask) == 0){
                                result.erase(result.begin() + i);
                                keepMovie = false;
                                break;
                            }
                        }
                        break;
                    }
                    case DURATION:{
                        unsigned int movieDuration = movie->getRuntimeMinutes();
                        if(movieDuration < duration.start || movieDuration > duration.end){
                            result.erase(result.begin() + i);
                            keepMovie = false;
                        }
                        break;
                    }
                    case RELEASE_YEAR:{
                        if(movie->getStartYear() != releaseYear){
                            result.erase(result.begin() + i);
                            keepMovie = false;
                        }
                        break;
                    }
                    case YEAR_INTERVAL:{
                        
                        break;
                    }
                }
                if (keepMovie == false) break;
            }
        }
    }

    return result;
}