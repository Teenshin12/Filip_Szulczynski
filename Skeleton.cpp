#include "Skeleton.h"
#include <cmath>
#include <cstdlib>

Skeleton::Skeleton(float speed, sf::Vector2f startPosition){

    skeletonDot.setRadius(20);
    skeletonDot.setOrigin(20,20);
    skeletonDot.setFillColor(sf::Color::Red);

    skeletonRadius.setRadius(radius);
    skeletonRadius.setOrigin(radius,radius);
    skeletonRadius.setFillColor(radiusSphereColor);

    skeletonTexture.loadFromFile("skeleton.png");
    skeletonSprite.setTexture(skeletonTexture);
    skeletonSprite.setOrigin(16,19);
    skeletonSprite.setScale(0.5,0.5);

    this->speed = speed;
    this->startPosition = startPosition;

    skeletonSprite.setPosition(startPosition);
    skeletonRadius.setPosition(startPosition);
    skeletonDot.setPosition(startPosition);
}

void Skeleton::updateDeltaTime(float deltaTime){
    this->deltaTime = deltaTime;
}

void Skeleton::move(sf::Vector2f direction){

    sf::Vector2f positionDifference = direction - skeletonPosition;

    float distance = sqrt(positionDifference.x * positionDifference.x + positionDifference.y * positionDifference.y);

    direction = {positionDifference.x / (std::abs(positionDifference.x) + std::abs(positionDifference.y)),
                 positionDifference.y / (std::abs(positionDifference.x) + std::abs(positionDifference.y))};

    if (distance < radius*1.1){
        skeletonSprite.move(speed * direction * deltaTime);
        skeletonRadius.setPosition(skeletonPosition);
    }

    skeletonPosition = skeletonSprite.getPosition();
    skeletonDot.setPosition(skeletonPosition.x - 6, skeletonPosition.y - 7);
}

sf::Vector2f Skeleton::returnPosition(){
    return skeletonPosition;
}

void Skeleton::drawGame(sf::RenderWindow &window){
    window.draw(skeletonRadius);
    window.draw(skeletonSprite);
}

void Skeleton::drawMinimap(sf::RenderWindow &window){
    window.draw(skeletonDot);
}

sf::Sprite Skeleton::returnSprite(){
    return skeletonSprite;
}
