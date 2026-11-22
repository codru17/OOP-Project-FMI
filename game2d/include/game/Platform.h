#pragma once

#include "engine/Entity.h"

class Platform : public Entity {
public:
    Platform(sf::Vector2f position, sf::Vector2f size);

    void update(float dt) override;
    void draw(sf::RenderTarget& target) const override;

private:
    sf::RectangleShape m_shape; // dreptunghiul desenat pe ecran (pozitia si marimea copiate din Entity la constructie)
};
