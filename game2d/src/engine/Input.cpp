#include "engine/Input.h"


bool Input::isValid(sf::Keyboard::Key key) {
    return key != sf::Keyboard::Key::Unknown && KEY_COUNT > static_cast<std::size_t>(key);
}

std::size_t Input::toIndex(sf::Keyboard::Key key) {
    return static_cast<std::size_t>(key);
}

bool Input::isDown(sf::Keyboard::Key key) const {
    if (!isValid(key)) {
        return false;
    }
    return m_current[toIndex(key)];
}

bool Input::isPressed(sf::Keyboard::Key key) const {
    if (!isValid(key)) {
        return false;
    }
    std::size_t index = toIndex(key);
    return m_current[index] && !m_previous[index];
}

bool Input::isReleased(sf::Keyboard::Key key) const {
    if (!isValid(key)) {
        return false;
    }
    std::size_t index = toIndex(key);
    return !m_current[index] && m_previous[index];
}

void Input::endStep() {
    m_previous = m_current;
}

void Input::handleEvent(const sf::Event& event) {
    if(auto *keyPressed = event.getIf<sf::Event::KeyPressed>(); keyPressed != nullptr) {
        if (isValid(keyPressed->code)) {
            m_current[toIndex(keyPressed->code)] = true;
        }
    } else if(auto *keyReleased = event.getIf<sf::Event::KeyReleased>(); keyReleased != nullptr) {
        if (isValid(keyReleased->code)) {
            m_current[toIndex(keyReleased->code)] = false;
        }
    } else if(event.is<sf::Event::FocusLost>()) {
        m_current.fill(false);
    }
}


