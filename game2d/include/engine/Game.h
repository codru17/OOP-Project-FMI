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
    static constexpr unsigned int WIDTH = 1280;          // latimea ferestrei, in pixeli
    static constexpr unsigned int HEIGHT = 720;          // inaltimea ferestrei, in pixeli
    static constexpr unsigned int FRAMERATE_LIMIT = 144; // cate cadre se deseneaza cel mult pe secunda (FPS maxim)
    static constexpr float TIME_STEP = 1.0f / 60.0f;     // durata unui update de logica (pasul fix): 1/60 s
    static constexpr float MAX_FRAME_TIME = 0.25f;       // plafon pentru timpul unui cadru, ca jocul sa nu inghete dupa o pauza
    static constexpr const char* TITLE = "Game2D";       // textul din bara de titlu a ferestrei

    sf::RenderWindow m_window;  // fereastra jocului: primeste evenimente si pe ea se deseneaza totul
    sf::Clock m_clock;          // cronometru: masoara timpul real scurs intre doua cadre
    Input m_input;              // starea tastaturii (tinuta / tocmai apasata / tocmai eliberata)
    float m_accumulator = 0.f;  // timp real (secunde) inca nesimulat de update-uri
    int m_updateCount = 0;      // debug: cate update-uri au rulat in secunda curenta
    float m_debugTime = 0.f;    // debug: secunde de joc scurse de la ultima afisare a contorului

    void processEvents();
    void update(float dt);
    void render();
};
