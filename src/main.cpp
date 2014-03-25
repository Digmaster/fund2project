#include "GameEngine.h"
#include <exception>
#include <iostream>

int main() {
    // TODO (Thomas Luppi#1#03/07/14): Add input of parameters and put them in some sort of "Temporary Vector" in the options
    GameEngine eng;
    try{
        eng.go();
    }
    catch(std::exception &e) {
        std::cout << e.what();
    }
}
