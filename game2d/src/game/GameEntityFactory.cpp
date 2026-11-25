#include "game/GameEntityFactory.h"
#include "game/Platform.h"
#include "game/Player.h"
#include "engine/LevelLoadError.h"

GameEntityFactory::GameEntityFactory(const Input &input) : m_input(input) {}

std::unique_ptr<Entity> GameEntityFactory::create(char symbol, sf::Vector2f position) const {
    switch(symbol) {
        case '#':
            return std::make_unique<Platform>(position, sf::Vector2f {EntityFactory::TILE_SIZE, EntityFactory::TILE_SIZE});
        case 'P':
            return std::make_unique<Player>(position, m_input);
        case '.':
            return nullptr;
        default:
            throw LevelLoadError("simbol necunoscut");
    }
}

