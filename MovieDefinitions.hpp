#pragma once

#include <map>
#include <cstddef> 


namespace IndiceConfig {
    const int ID_OFFSET = 7917518; //first id
    const size_t INDEX_SIZE = (9195182 - ID_OFFSET)/2 + 1; //last id
    const size_t NULL_INDEX = -1; // Representa um slot vazio no índice
}

//Masks for each genre
namespace Genres
{
    const unsigned int action        = 1 << 0;   // 1
    const unsigned int adult         = 1 << 1;   // 2
    const unsigned int adventure     = 1 << 2;   // 3
    const unsigned int animation     = 1 << 3;   // 4
    const unsigned int biography     = 1 << 4;   // 5
    const unsigned int comedy        = 1 << 5;   // 6
    const unsigned int crime         = 1 << 6;   // 7
    const unsigned int documentary   = 1 << 7;   // 8
    const unsigned int drama         = 1 << 8;   // 9
    const unsigned int family        = 1 << 9;   // 10
    const unsigned int fantasy       = 1 << 10;  // 11
    const unsigned int game_Show     = 1 << 11;  // 12
    const unsigned int history       = 1 << 12;  // 13
    const unsigned int horror        = 1 << 13;  // 14
    const unsigned int music         = 1 << 14;  // 15
    const unsigned int musical       = 1 << 15;  // 16
    const unsigned int mystery       = 1 << 16;  // 17
    const unsigned int news          = 1 << 17;  // 18
    const unsigned int reality_TV    = 1 << 18;  // 19
    const unsigned int romance       = 1 << 19;  // 20
    const unsigned int sci_Fi        = 1 << 20;  // 21
    const unsigned int _short        = 1 << 21;  // 22
    const unsigned int sport         = 1 << 22;  // 23
    const unsigned int talk_Show     = 1 << 23;  // 24
    const unsigned int thriller      = 1 << 24;  // 25
    const unsigned int war           = 1 << 25;  // 26
    const unsigned int western       = 1 << 26;  // 27
}

// Maps for Genres
const std::map<unsigned int, std::string> genresMap = {
    {Genres::action, "Action"},
    {Genres::adult, "Adult"},
    {Genres::adventure, "Adventure"},
    {Genres::animation, "Animation"},
    {Genres::biography, "Biography"},
    {Genres::comedy, "Comedy"},
    {Genres::crime, "Crime"},
    {Genres::documentary, "Documentary"}, 
    {Genres::drama, "Drama"},
    {Genres::family, "Family"},
    {Genres::fantasy, "Fantasy"},
    {Genres::game_Show, "Game-Show"},
    {Genres::history, "History"},
    {Genres::horror, "Horror"},
    {Genres::music, "Music"},
    {Genres::musical, "Musical"},
    {Genres::mystery, "Mystery"},
    {Genres::news, "News"},
    {Genres::reality_TV, "Reality-TV"},
    {Genres::romance, "Romance"},
    {Genres::sci_Fi, "Sci-Fi"},
    {Genres::_short, "Short"},
    {Genres::sport, "Sport"},
    {Genres::talk_Show, "Talk-Show"},
    {Genres::thriller, "Thriller"},
    {Genres::war, "War"},
    {Genres::western, "Western"}
};

const std::map<std::string, unsigned int> stringToGenreMask = {
    {"Action", Genres::action},
    {"Adult", Genres::adult},
    {"Adventure", Genres::adventure},
    {"Animation", Genres::animation},
    {"Biography", Genres::biography},
    {"Comedy", Genres::comedy},
    {"Crime", Genres::crime},
    {"Documentary", Genres::documentary},
    {"Drama", Genres::drama},
    {"Family", Genres::family},
    {"Fantasy", Genres::fantasy},
    {"Game-Show", Genres::game_Show},
    {"History", Genres::history},
    {"Horror", Genres::horror},
    {"Music", Genres::music},
    {"Musical", Genres::musical},
    {"Mystery", Genres::mystery},
    {"News", Genres::news},
    {"Reality-TV", Genres::reality_TV},
    {"Romance", Genres::romance},
    {"Sci-Fi", Genres::sci_Fi},
    {"Short", Genres::_short},
    {"Sport", Genres::sport},
    {"Talk-Show", Genres::talk_Show},
    {"Thriller", Genres::thriller},
    {"War", Genres::war},
    {"Western", Genres::western}
};

//Masks for each type
namespace TitleTypes
{
    const unsigned short movie        = 1 << 0;   // 1
    const unsigned short _short       = 1 << 1;   // 2
    const unsigned short tvEpisode    = 1 << 2;   // 3
    const unsigned short tvMiniSeries = 1 << 3;   // 4
    const unsigned short tvMovie      = 1 << 4;   // 5
    const unsigned short tvSeries     = 1 << 5;   // 6
    const unsigned short tvShort      = 1 << 6;   // 7
    const unsigned short tvSpecial    = 1 << 7;   // 8
    const unsigned short video        = 1 << 8;   // 9
    const unsigned short videoGame    = 1 << 9;   // 10
}

// Maps for TitleTypes
const std::map<unsigned short, std::string> titleTypesMap = {
    {TitleTypes::movie, "Movie"},
    {TitleTypes::_short, "Short"},
    {TitleTypes::tvEpisode, "TV Episode"},
    {TitleTypes::tvMiniSeries, "TV Mini-Series"},
    {TitleTypes::tvMovie, "TV Movie"},
    {TitleTypes::tvSeries, "TV Series"},
    {TitleTypes::tvShort, "TV Short"},
    {TitleTypes::tvSpecial, "TV Special"},
    {TitleTypes::video, "Video"},
    {TitleTypes::videoGame, "Video Game"}
};

const std::map<std::string, unsigned short> stringToTitleTypeMask = {
    {"movie", TitleTypes::movie},
    {"short", TitleTypes::_short},
    {"tvEpisode", TitleTypes::tvEpisode},
    {"tvMiniSeries", TitleTypes::tvMiniSeries},
    {"tvMovie", TitleTypes::tvMovie},
    {"tvSeries", TitleTypes::tvSeries},
    {"tvShort", TitleTypes::tvShort},
    {"tvSpecial", TitleTypes::tvSpecial},
    {"video", TitleTypes::video},
    {"videoGame", TitleTypes::videoGame}
};