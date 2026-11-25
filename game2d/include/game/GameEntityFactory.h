#pragma once

#include "engine/EntityFactory.h"
#include "engine/Input.h"

class GameEntityFactory : public EntityFactory {
    public:
        explicit GameEntityFactory(const Input& input);
        std::unique_ptr<Entity> create(char symbol, sf::Vector2f position) const override;
    private:
        const Input& m_input;
};