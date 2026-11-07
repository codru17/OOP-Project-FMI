#include "engine/Game.h"

Game::Game() : m_window(sf::VideoMode(sf::Vector2u{WIDTH,HEIGHT}), TITLE) {
    m_window.setFramerateLimit(FRAMERATE_LIMIT);
}

void Game::processEvents() {
        while (auto event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                m_window.close();
        }
            if(auto *keyPressed = event->getIf<sf::Event::KeyPressed>(); keyPressed != nullptr && keyPressed->code == sf::Keyboard::Key::Escape) {
                m_window.close();
            }
    }
}

