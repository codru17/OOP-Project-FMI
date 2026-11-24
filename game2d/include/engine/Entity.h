#pragma once

#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual ~Entity() = default;
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& target) const = 0;

    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    sf::Vector2f getVelocity() const;
    sf::FloatRect getBounds() const;

    void setPosition(sf::Vector2f position);
    void setVelocity(sf::Vector2f velocity);

    virtual bool isSolid() const {return false;}
    virtual bool isDynamic() const {return false;}
    bool isOnGround() const {return m_onGround;}
    void setOnGround(bool onGround) {m_onGround = onGround;} 

protected:
    Entity(const sf::Vector2f& position, const sf::Vector2f& size);

private:
    sf::Vector2f m_position; // coltul stanga-sus al entitatii, in pixeli (in SFML axa y creste in jos)
    sf::Vector2f m_velocity; // viteza entitatii, in pixeli pe secunda; porneste (0,0)
    sf::Vector2f m_size;     // latimea (x) si inaltimea (y) entitatii, in pixeli; fixata la constructie
    bool m_onGround = false;
};
