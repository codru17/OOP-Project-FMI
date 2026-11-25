#include "game/Player.h"

#include <algorithm>

Player::Player(sf::Vector2f position, const Input& input)
    : Entity(position, {SIZE, SIZE}), m_input(input), m_shape({SIZE, SIZE}) {
    m_shape.setFillColor(sf::Color::Black);
}

void Player::update(float dt) {
    float direction = 0.f;

    if (m_input.isDown(sf::Keyboard::Key::A) || m_input.isDown(sf::Keyboard::Key::Left)) direction -= 1.f;
    if (m_input.isDown(sf::Keyboard::Key::D) || m_input.isDown(sf::Keyboard::Key::Right)) direction += 1.f;

    float vx = direction * MOVE_SPEED;
    float vy = getVelocity().y + GRAVITY * dt;
    vy = std::min(vy, MAX_FALL_SPEED);

    if (isOnGround() && (m_input.isPressed(sf::Keyboard::Key::W) ||
                         m_input.isPressed(sf::Keyboard::Key::Up) ||
                         m_input.isPressed(sf::Keyboard::Key::Space))) {
        vy = -JUMP_SPEED;
    }

    setVelocity(sf::Vector2f{vx, vy});
    setPosition(getPosition() + getVelocity() * dt);
}

void Player::draw(sf::RenderTarget& target) const {
    sf::RenderStates states;
    states.transform.translate(getPosition());
    target.draw(m_shape, states);
}
