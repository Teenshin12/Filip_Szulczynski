#ifndef SKELETON_H
#define SKELETON_H

#include <GameObjects.h>

class Skeleton: public GameObjects{
private:
    sf::CircleShape skeletonDot;
    sf::CircleShape skeletonRadius;
    sf::Texture skeletonTexture;
    sf::Sprite skeletonSprite;
    sf::Vector2f skeletonPosition;
    sf::Color radiusSphereColor = {76,0,152,30};
    float deltaTime = 0;
    float speed = 10;
    float radius = 50;
    sf::Vector2f startPosition = {0,0};
public:
    Skeleton(float speed, sf::Vector2f startPosition);
    virtual void updateDeltaTime(float deltaTime);
    virtual void move(sf::Vector2f direction);
    virtual sf::Vector2f returnPosition();
    virtual void drawGame(sf::RenderWindow &window);
    virtual void drawMinimap(sf::RenderWindow &window);
    virtual sf::Sprite returnSprite();
};

#endif // SKELETON_H
