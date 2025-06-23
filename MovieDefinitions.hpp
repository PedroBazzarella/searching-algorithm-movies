#pragma once

#include <cstddef>
#include <string>
#include <vector>


namespace IndexConfig {
    const int ID_OFFSET = 7917518; //first id
    const size_t INDEX_SIZE = (9195182 - ID_OFFSET)/2 + 1; //last id
    const size_t NULL_INDEX = -1; // represents an empty slot in the index
    const size_t NUM_GENRES = 27;
    const size_t NUM_TITTLE_TYPES = 10;
}

//Movie Genres
/*
    Define a list of all movie genres
*/
#define GENRES_LIST          \
    X(action,      "Action")      \
    X(adult,       "Adult")       \
    X(adventure,   "Adventure")   \
    X(animation,   "Animation")   \
    X(biography,   "Biography")   \
    X(comedy,      "Comedy")      \
    X(crime,       "Crime")       \
    X(documentary, "Documentary") \
    X(drama,       "Drama")       \
    X(family,      "Family")      \
    X(fantasy,     "Fantasy")     \
    X(game_Show,   "Game-Show")   \
    X(history,     "History")     \
    X(horror,      "Horror")      \
    X(music,       "Music")       \
    X(musical,     "Musical")     \
    X(mystery,     "Mystery")     \
    X(news,        "News")        \
    X(reality_TV,  "Reality-TV")  \
    X(romance,     "Romance")     \
    X(sci_Fi,      "Sci-Fi")      \
    X(_short,      "Short")       \
    X(sport,       "Sport")       \
    X(talk_Show,   "Talk-Show")   \
    X(thriller,    "Thriller")    \
    X(war,         "War")         \
    X(western,     "Western")

/*
    Generate namespace from GENRES_LIST
*/
// name -> bitmask
namespace Genres {
#define X(name, label) constexpr unsigned int name = 1u << __COUNTER__;
    GENRES_LIST
#undef X
}

// pos in bitmask -> label
inline std::vector<std::string> GenresNameList = {
#define X(name, label) label,
    GENRES_LIST
#undef X
};

/*
    Generate function from GENRES_LIST to return bitmask of a genre from string
*/
inline unsigned int genreFromString(const std::string& s) {
#define X(name, label) if (s == label) return Genres::name;
    GENRES_LIST
#undef X
    return 0;
}

//Movie Types
/*
    Define a list of all movie types
*/
#define TYPES_LIST          \
    X(movie,        "Movie")          \
    X(_short,       "Short")          \
    X(tvEpisode,    "TV Episode")     \
    X(tvMiniSeries, "TV Mini-Series") \
    X(tvMovie,      "TV Movie")       \
    X(tvSeries,     "TV Series")      \
    X(tvShort,      "TV Short")       \
    X(tvSpecial,    "TV Special")     \
    X(video,        "Video")          \
    X(videoGame,    "Video Game")

/*
    Generate namespace from TYPES_LIST
*/
// name -> bitmask
enum { GENRES_LIST_SIZE = __COUNTER__ }; //Get __COUNTER__ value
namespace TitleTypes {
#define X(name, label) constexpr unsigned short name = 1u << (__COUNTER__ - GENRES_LIST_SIZE);
    TYPES_LIST
#undef X
}

// pos in bitmask -> label
inline std::vector<std::string> TypesNameList = {
#define X(name, label) label,
    TYPES_LIST
#undef X
};

/*
    Generate function from TYPES_LIST to return bitmask of a type from string
*/
inline unsigned short typeFromString(const std::string& s) {
#define X(name, label) if (s == label) return TitleTypes::name;
    TYPES_LIST
#undef X
    return 0;
}