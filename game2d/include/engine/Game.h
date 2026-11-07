#pragma once

#include <SFML/Graphics.hpp>

#include "engine/Input.h"

class Game {
public:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void run();

private:
    static constexpr unsigned int WIDTH = 1280;
    static constexpr unsigned int HEIGHT = 720;
    static constexpr unsigned int FRAMERATE_LIMIT = 144;
    static constexpr float TIME_STEP = 1.0f / 60.0f;
    static constexpr float MAX_FRAME_TIME = 0.25f;
    static constexpr const char* TITLE = "Game2D";

    sf::RenderWindow m_window;
    sf::Clock m_clock;
    Input m_input;
    float m_accumulator = 0.f;
    int m_updateCount = 0;
    float m_debugTime = 0.f;

    void processEvents();
    void update(float dt);
    void render();
};
