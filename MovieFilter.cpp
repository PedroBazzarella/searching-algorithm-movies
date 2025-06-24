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

std::vector<Movies> MovieFilter::Filter(std::vector<Movies> movies) const{
    std::vector<Movies> result = {};
    
    for(movieFilterType filter : filterTypes){
        switch(filter){
            case MOVIE_TYPE:
                if(result.empty()){
                    result = database->getTittleTypeList(movieTypeMask[0]);
                }
            break;
            case MOVIE_GENRE:

            break;
            case DURATION:

            break;
            case RELEASE_YEAR:

            break;
            case YEAR_INTERVAL:

            break;
        }
    }
}