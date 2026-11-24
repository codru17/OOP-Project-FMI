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
    resolveCollisions();
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

void Game::resolveCollisions() {
    for(auto& entity : m_entities) {
        if(!entity->isDynamic()) continue;
        entity->setOnGround(false);
        for(auto& ent : m_entities) {
            if(!ent->isSolid())continue;

            auto intersection = (entity->getBounds()).findIntersection(ent->getBounds());
            if(!intersection)continue;
            auto pos = entity->getPosition();
            auto vel = entity->getVelocity();
            auto cent1 = (entity->getBounds()).getCenter();
            auto cent2 = (ent->getBounds()).getCenter();
            
            if(intersection->size.x <intersection->size.y) {
                if(cent1.x < cent2.x){
                    pos.x -= intersection->size.x;
                    vel.x = 0;
                }
                else {
                    pos.x += intersection->size.x;
                    vel.x=0;
                }
            } else {
                if(cent1.y < cent2.y) {
                    pos.y -= intersection->size.y;
                    vel.y = 0;
                    entity->setOnGround(true);
                }
                else {
                    pos.y += intersection->size.y;
                    vel.y=0;
                }
            }
            entity->setPosition(pos);
            entity->setVelocity(vel);
        }
        // marginile ferestrei: entitatea dinamica nu are voie sa iasa pe stanga sau pe dreapta
        auto pos = entity->getPosition();
        auto vel = entity->getVelocity();
        float width = entity->getSize().x;

        if (pos.x < 0.f) {
            pos.x = 0.f;
            vel.x = 0.f;
        } else if (pos.x + width > WIDTH) {
            pos.x = WIDTH - width;
            vel.x = 0.f;
        }

        entity->setPosition(pos);
        entity->setVelocity(vel);
    }
}