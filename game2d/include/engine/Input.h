#pragma once

#include <array>
#include <cstddef>

#include <SFML/Window.hpp>

class Input {
public:
    void handleEvent(const sf::Event& event);
    void endStep();

    bool isDown(sf::Keyboard::Key key) const;
    bool isPressed(sf::Keyboard::Key key) const;
    bool isReleased(sf::Keyboard::Key key) const;

private:
    static constexpr std::size_t KEY_COUNT = sf::Keyboard::KeyCount;

    std::array<bool, KEY_COUNT> m_current = {};
    std::array<bool, KEY_COUNT> m_previous = {};

    static std::size_t toIndex(sf::Keyboard::Key key);
    static bool isValid(sf::Keyboard::Key key);
};
