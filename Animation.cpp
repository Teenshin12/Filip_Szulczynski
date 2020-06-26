#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageSize, float frameTime){
    // GET VARIABLES //
    this->imageSize = imageSize;
    this->frameTime = frameTime;
    // SET VARIABLES //
    time = 0.0f;
    currentImage.x = 0;
    currentImage.y = 0;

    uvRect.width = texture->getSize().x / float(imageSize.x);
    uvRect.height = texture->getSize().y / float(imageSize.y);
}


void Animation::Update(int row, float deltaTime){
    currentImage.y = row;
    time += deltaTime;

    if(time >= frameTime){
        time -= frameTime;
        currentImage.x++;
        if(currentImage.x >= imageSize.x){
            currentImage.x = 0;
        }
    }

    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}
