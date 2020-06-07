#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <sfml\Graphics.hpp>

#include <vector>
#include <fstream>

class MapLoader{
private:
    std::vector <sf::Sprite> groundLayer; //ground sprites
    std::vector <sf::Sprite> wallLayer; //all collision block
    float scale;
    sf::Texture spriteSheet; //all textures to set
public:
    MapLoader(float scale);
    void loadLayers(std::string mapNumber);
    void draw(sf::RenderWindow &window);
};

#endif // MAPLOADER_H
