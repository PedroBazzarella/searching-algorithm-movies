#include "MovieDataBase.hpp"
#include <iostream>
#include <chrono>

int main(){
    Movies movie(7917518, 2, "The Battle II", "The Battle II", false, 2008, 0, 0, 2097153);

    std::string data = movie.toString();

    std::cout << data << std::endl;

    MovieDataBase database;
    std::string fileName = "testFile.txt";

    
    std::cout << ">>> Loading movies from file: " << fileName << "..." << std::endl;
    database.loadMoviesFromTXT(fileName);

    std::cout << "Pressione Enter para sair..." << std::endl;
    std::cin.get(); 

    return 0;

}   