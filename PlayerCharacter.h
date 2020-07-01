#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include <SFML/Graphics.hpp>

#include <GameObjects.h>

#include "Animation.h"

class PlayerCharacter: public GameObjects{
private:
    sf::CircleShape playerDot;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    Animation playerAnimation;
    sf::Vector2f playerPosition;
    std::vector <sf::Sprite> wallLayer;
    float deltaTime;
public:
    PlayerCharacter();
    virtual void updateDeltaTime(float deltaTime);
    virtual void move(sf::Vector2f direction);
    virtual sf::Vector2f returnPosition();
    virtual void drawGame(sf::RenderWindow &window);
    virtual void drawMinimap(sf::RenderWindow &window);
    void loadWalls(std::vector <sf::Sprite> wallLayer);
    void setPosition(sf::Vector2f position);
    virtual sf::Sprite returnSprite();
};

#endif // PLAYERCHARACTER_H
