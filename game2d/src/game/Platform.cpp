#include "game/Platform.h"

Platform::Platform(sf::Vector2f position, sf::Vector2f size) : Entity(position, size ), m_shape(size) {
    m_shape.setPosition(position);
    m_shape.setFillColor(sf::Color::Green);
}
    void Platform::update(float) {}
    void Platform::draw(sf::RenderTarget& target) const {
        target.draw(m_shape);
    }

