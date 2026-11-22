#include "game/Player.h"
#include "engine/Input.h"

Player::Player(sf::Vector2f position, const Input& input) : Entity(position, {SIZE,SIZE}), m_input(input), m_shape({SIZE,SIZE}) {
    m_shape.setFillColor(sf::Color::Black);
    m_shape.setPosition(position);
}

void Player::update(float dt) {
    float direction = 0;
    if(m_input.isDown(sf::Keyboard::Key::A) || m_input.isDown(sf::Keyboard::Key::Left)) direction -=1;
    if(m_input.isDown(sf::Keyboard::Key::D) || m_input.isDown(sf::Keyboard::Key::Right)) direction +=1;
    float x=direction * MOVE_SPEED, y=0;
    setVelocity(sf::Vector2f {x,y});
    setPosition(getPosition() + getVelocity() * dt);
    m_shape.setPosition(getPosition());
}

void Player::draw(sf::RenderTarget& target) const {
    target.draw(m_shape);
}