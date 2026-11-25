#pragma once

#include "engine/Entity.h"
#include "engine/Input.h"

class Player : public Entity {
public:
    Player(sf::Vector2f position, const Input& input);

    void update(float dt) override;
    void draw(sf::RenderTarget& target) const override;
    bool isDynamic() const override {return true;}

private:
    static constexpr float MOVE_SPEED = 300; // viteza orizontala a jucatorului, in pixeli pe secunda
    static constexpr float SIZE = 48;        // latura patratului jucatorului, in pixeli
    static constexpr float GRAVITY = 1800;       // acceleratia gravitationala, in pixeli pe secunda la patrat (in jos = y pozitiv)
    static constexpr float JUMP_SPEED = 800;     // viteza initiala a sariturii, in pixeli pe secunda (aplicata in sus, cu minus)
    static constexpr float MAX_FALL_SPEED = 1000; // viteza maxima de cadere, in pixeli pe secunda (evita trecerea prin platforme)

    const Input& m_input;       // referinta la tastatura jocului (primita din Game); jucatorul doar o citeste
    sf::RectangleShape m_shape; // patratul desenat; sta in (0,0), pozitia entitatii se aplica la desenare prin RenderStates
};
