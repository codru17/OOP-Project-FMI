#pragma once

#include "engine/Entity.h"
#include "engine/Input.h"

class Player : public Entity {
public:
    Player(sf::Vector2f position, const Input& input);

    void update(float dt) override;
    void draw(sf::RenderTarget& target) const override;

private:
    static constexpr float MOVE_SPEED = 300; // viteza orizontala a jucatorului, in pixeli pe secunda
    static constexpr float SIZE = 48;        // latura patratului jucatorului, in pixeli

    const Input& m_input;       // referinta la tastatura jocului (primita din Game); jucatorul doar o citeste
    sf::RectangleShape m_shape; // patratul desenat pe ecran; pozitia lui se sincronizeaza cu Entity in update
};
