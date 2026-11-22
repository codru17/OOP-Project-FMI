#include "engine/Game.h"
#include <utility>
#include <algorithm>
#include <iostream>

Game::Game() : m_window(sf::VideoMode(sf::Vector2u{WIDTH, HEIGHT}), TITLE) {
    m_window.setFramerateLimit(FRAMERATE_LIMIT);
    m_window.setKeyRepeatEnabled(false);
}

void Game::processEvents() {
    while (auto event = m_window.pollEvent()) {
        m_input.handleEvent(*event);

        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }

        if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
            keyPressed != nullptr && keyPressed->code == sf::Keyboard::Key::Escape) {
            m_window.close();
        }
    }
}

void Game::run() {
    while (m_window.isOpen()) {
        processEvents();

        float frameTime = m_clock.restart().asSeconds();
        frameTime = std::min(frameTime, MAX_FRAME_TIME);
        m_accumulator += frameTime;

        while (m_accumulator >= TIME_STEP) {
            update(TIME_STEP);
            m_accumulator -= TIME_STEP;
        }

        render();
    }
}

void Game::update(float dt) {
    m_debugTime += dt;
    m_updateCount++;
    if (m_debugTime >= 1.0f) {
        std::cout << "Updates per second: " << m_updateCount << '\n';
        m_debugTime -= 1.0f;
        m_updateCount = 0;
    }

    for(auto& entity : m_entities) {
        entity->update(dt);
    } 

    m_input.endStep();
}

void Game::render() {
    m_window.clear(sf::Color::Blue);
    for(auto& entity : m_entities) {
        entity->draw(m_window);
    }
    m_window.display();
}

void Game::addEntity(std::unique_ptr<Entity> entity) {
    m_entities.push_back(std::move(entity));
}

const Input& Game::getInput() const  {
    return m_input;
}
