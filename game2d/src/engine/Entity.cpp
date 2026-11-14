#include <engine/Entity.h>

Entity::Entity(const sf::Vector2f& position, const sf::Vector2f& size) : m_position(position), m_velocity(), m_size(size) {}

sf::Vector2f Entity::getPosition() const {
    return m_position;
}

sf::Vector2f Entity::getVelocity() const {
    return m_velocity;
}

sf::FloatRect Entity::getBounds() const {
    return sf::FloatRect(m_position, m_size);
}

sf::Vector2f Entity::getSize() const {
    return m_size;
}

void Entity::setPosition(sf::Vector2f position) {
    m_position = position;
}

void Entity::setVelocity(sf::Vector2f velocity) {
    m_velocity = velocity;
}
