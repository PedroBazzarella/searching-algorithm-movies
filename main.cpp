#include "MovieDataBase.hpp"
#include "MovieDefinitions.hpp"
#include <iostream>
#include <chrono>

int main()
{
    Movies movie(7917518, 2, "The Battle II", "The Battle II", false, 2008, 0, 0, 2097153);

    std::string data = movie.toString();

    std::cout << data << std::endl;

    MovieDataBase database;
    std::string fileName = "C:\\Users\\Waleska\\Documents\\Faculdade\\ProjetoI_TBO_2025\\searching-algorithm-movies\\testFile.txt";

    std::cout << ">>> Loading movies from file: " << fileName << "..." << std::endl;
    database.loadMoviesFromTXT(fileName);

    // teste busca na hash por id
    std::string filme = (database.findMovieByID(7917538))->toString();
    std::cout << ">>> Busca por ID: " + filme << std::endl;

    // teste busca por lista de genero
    std::cout << ">>> Busca por lista de genero drama: " << std::endl;
    const auto &listMovies = database.getGenreList(Genres::drama);
    std::cout << listMovies.size() << std::endl;

    for (size_t i = 0; i < listMovies.size(); ++i)
    {
        unsigned int movieId = listMovies[i];

        const Movies *movie = database.findMovieByID(movieId);

        if (movie != nullptr)
        {
            std::cout << movie->toString() << std::endl;
        }
        else
        {
            std::cout << "AVISO: O filme com ID " << movieId
                      << " estava na lista de Drama, mas nao foi encontrado na base de dados principal."
                      << std::endl;
        }
    }

    // teste busca por lista de tipo de fillme
    std::cout << ">>> Busca por lista de short film: " << std::endl;
    const auto & listMovies2 = database.getTittleTypeList(TitleTypes::_short);
    std::cout << listMovies2.size() << std::endl;

    for (size_t i = 0; i < listMovies2.size(); ++i)
    {
        unsigned int movieId = listMovies2[i];

        const Movies *movie = database.findMovieByID(movieId);

        if (movie != nullptr)
        {
            std::cout << movie->toString() << std::endl;
        }
        else
        {
            std::cout << "AVISO: O filme com ID " << movieId
                      << " estava na lista de Drama, mas nao foi encontrado na base de dados principal."
                      << std::endl;
        }
    }

    std::cout << "Pressione Enter para sair..." << std::endl;
    std::cin.get();

    return 0;

}