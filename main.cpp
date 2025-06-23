#include "MovieDataBase.hpp"
#include "MovieDefinitions.hpp"
#include <iostream>
#include <chrono>

int main()
{
    MovieDataBase database;
    std::string fileName = "testFile.txt";

    std::cout << ">>> Loading movies from file: " << fileName << "..." << std::endl;
    database.loadMoviesFromTXT(fileName);

    std::cout << "Pressione Enter para sair..." << std::endl;
    std::cin.get();

    return 0;

}