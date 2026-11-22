#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>

#include "game/Platform.h"
#include "engine/Game.h"

int main() {
    try {
        Game game;
        game.addEntity(std::make_unique<Platform>(sf::Vector2f{0,660},sf::Vector2f{1280,60}));
        game.addEntity(std::make_unique<Platform>(sf::Vector2f{250,520},sf::Vector2f{220,24}));
        game.addEntity(std::make_unique<Platform>(sf::Vector2f{700,400},sf::Vector2f{220,24}));
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
