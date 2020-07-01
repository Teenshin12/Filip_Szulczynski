#ifndef ANIMATION_H
#define ANIMATION_H

#include <sfml\Graphics.hpp>

class Animation{
public:
    Animation(sf::Texture* texture = 0, sf::Vector2u ImageCount = {0,0}, float frameTime = 0);

    sf::IntRect uvRect;

    void Update(int row, float deltaTime);

private:
    sf::Vector2u imageSize;
    sf::Vector2u currentImage;

    float time;
    float frameTime;
};

#endif // ANIMATION_H
