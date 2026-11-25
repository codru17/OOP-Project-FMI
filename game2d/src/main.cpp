#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>

#include "engine/Game.h"
#include "game/Platform.h"
#include "game/Player.h"
#include "game/GameEntityFactory.h"

int main() {
    try {
        Game game;
        GameEntityFactory fact(game.getInput());
        game.loadLevel("assets/levels/level1.txt", fact);
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unknown exception occurred.\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
