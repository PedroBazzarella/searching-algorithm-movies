#include "MovieFilter.hpp"
#include "MovieDatabase.hpp"


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
std::vector<unsigned int> MovieFilter::Filter(std::vector<Movies> movies){
    std::vector<unsigned int> result = {}; // movies IDs
    
    /*
        Start result list
    */
    switch(filterTypes[0]){
        case MOVIE_TYPE:{
            /*
                Get smaller movie type list
            */
            int bestMovieList = -1;
            for(short i = 0; i < 16; ++i){
                if((1 << i & movieTypeMask) != 0){
                    if(bestMovieList == -1 || database.getTitleTypeListSize(1 << i) < database.getTitleTypeListSize(1 << bestMovieList)){
                        bestMovieList = i;
                    }
                }
            }
            std::vector<size_t> initialList = database.getTitleTypeList(1 << bestMovieList);
            result.assign(initialList.begin(), initialList.end());
            break;
        }
        case MOVIE_GENRE:{
            /*
                Get smaller movie genre list
            */
            int bestMovieList = -1;
            for(int i = 0; i < 31; ++i){
                if((1 << i & movieGenreMask) != 0){
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
            std::vector<unsigned int> initialList = database.getStartYearIndex()[database.getStartYearPosition(releaseYear)];
            result.assign(initialList.begin(), initialList.end());
            break;
        }
        case YEAR_INTERVAL:{

            break;
        }
    }

    

    return result;
}