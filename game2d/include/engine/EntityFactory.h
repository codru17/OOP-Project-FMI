#pragma once

#include <memory>
#include "engine/Entity.h"

class EntityFactory {
    public:
        virtual ~EntityFactory() = default ;
        virtual std::unique_ptr<Entity> create(char symbol,sf::Vector2f position) const = 0;
        static constexpr float TILE_SIZE = 40; //latura unui tile din grila nivelului, in pixeli
};
