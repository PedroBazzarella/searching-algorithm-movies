#include "MovieDataBase.hpp"
#include "MovieDefinitions.hpp"
#include "MovieFilter.hpp"
#include "InputReader.hpp"
#include <iostream>
#include <chrono>
#include <vector> //delete this line!!!

int main()
{
    MovieDataBase database(false);
    std::string fileName = "filmesCrop.txt";
    std::cout << ">>> Loading movies from file: " << fileName << "..." << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    database.loadMoviesFromTXT(fileName);

    InputReader reader;
    std::string input = "g.Romance,t._short";
    std::vector<unsigned int> result = reader.readAndSearch(database, input);

    for(size_t id : result){
        std::cout << database.findMovieByID(id)->toString() << std::endl;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_raw = end_time - start_time;
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration_raw);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "FINISHED LOADING: \t" << duration_ms.count() << " milliseconds." << std::endl;
    std::cout << "RESULTS: \t\t" << result.size() << " movies." << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    std::cout << "Pressione Enter para sair..." << std::endl;
    std::cin.get();

    return 0;

}