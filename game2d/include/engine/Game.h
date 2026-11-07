#pragma once
#include <SFML/Graphics.hpp>

class Game {
    public:
        Game();
        void run();
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        

    private:
        static constexpr unsigned int WIDTH = 1280;
        static constexpr unsigned int HEIGHT = 720;
        static constexpr float TIME_STEP = 1.0f / 60.0f;
        static constexpr float MAX_FRAME_TIME = .25f;
        static constexpr char* TITLE = "Game2D";
        static constexpr unsigned int FRAMERATE_LIMIT = 144;
        sf::RenderWindow m_window;
        sf::Clock m_clock;
        float m_accumulator = 0.f;
        int m_updateCount = 0;
        float m_debugTime = 0.f;
        

        void processEvents();
        void update(float dt);
        void render();

};