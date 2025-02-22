#include "Game/Game.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        Game game;
        game.run();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}