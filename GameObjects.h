#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <SFML/Graphics.hpp>

class GameObjects{
public:
    GameObjects();
    virtual void updateDeltaTime(float deltaTime) = 0;
    virtual void move(sf::Vector2f direction) = 0;
    virtual sf::Vector2f returnPosition() = 0;
    virtual void drawGame(sf::RenderWindow &window) = 0;
    virtual void drawMinimap(sf::RenderWindow &window) = 0;
    virtual sf::Sprite returnSprite() = 0;
    virtual ~GameObjects() = default;
};

#endif // GAMEOBJECTS_H
