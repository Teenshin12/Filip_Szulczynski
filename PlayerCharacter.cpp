#include "PlayerCharacter.h"
#include <iostream>

PlayerCharacter::PlayerCharacter(){
    playerDot.setRadius(20);
    playerDot.setOrigin(20,20);
    playerDot.setFillColor(sf::Color::Green);

    playerTexture.loadFromFile("player.png");
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition({16, 150});
    playerSprite.setOrigin(5,9);

    playerAnimation = {&playerTexture, sf::Vector2u(4,6), 0.3f};
}

void PlayerCharacter::updateDeltaTime(float deltaTime){
    this->deltaTime = deltaTime;
}

void PlayerCharacter::move(sf::Vector2f direction){
    int playerMovement = 0;
    if(direction.x != 0 || direction.y !=0){
        bool collisionX = false;
        bool collisionY = false;

        playerSprite.move(direction.x, 0);
        for(size_t i = 0; i < wallLayer.size(); i++){
            if(playerSprite.getGlobalBounds().intersects(wallLayer[i].getGlobalBounds())){ collisionX = true; i = wallLayer.size(); }
        }
        playerSprite.move(-direction.x, direction.y);
        for(size_t i = 0; i < wallLayer.size(); i++){
            if(playerSprite.getGlobalBounds().intersects(wallLayer[i].getGlobalBounds())){ collisionY = true; i = wallLayer.size(); }
        }
        playerSprite.move(direction.x, 0);

        if(playerSprite.getPosition().x < 4 || playerSprite.getPosition().x > 1594) collisionX = true;
        if(playerSprite.getPosition().y < 8 || playerSprite.getPosition().y > 19*16+12 ) collisionY = true;

        if(collisionX == false){
            if(direction.x < 0) playerMovement = 2;
            else if(direction.x > 0) playerMovement = 1;
        }
        else playerSprite.move(-direction.x, 0);
        if(collisionY == false){
            if(direction.y > 0) playerMovement = 4;
            else if(direction.y < 0) playerMovement = 3;
        }
        else playerSprite.move(0, -direction.y);
    }
    playerPosition = playerSprite.getPosition();
    playerDot.setPosition(playerPosition.x - 6, playerPosition.y - 7);

    playerAnimation.Update(playerMovement, deltaTime * 3);
    playerSprite.setTextureRect(playerAnimation.uvRect);
}

sf::Vector2f PlayerCharacter::returnPosition(){
    return playerPosition;
}

void PlayerCharacter::drawGame(sf::RenderWindow &window){
    window.draw(playerSprite);
}

void PlayerCharacter::drawMinimap(sf::RenderWindow &window){
    window.draw(playerDot);
}

sf::Sprite PlayerCharacter::returnSprite(){
    return playerSprite;
}

void PlayerCharacter::setPosition(sf::Vector2f position){
    playerSprite.setPosition(position);
}
void PlayerCharacter::loadWalls(std::vector<sf::Sprite> wallLayer){
    this->wallLayer = wallLayer;
}
