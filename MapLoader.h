#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <sfml\Graphics.hpp>

#include <vector>
#include <fstream>

class MapLoader{
private:
    std::vector <sf::Sprite> groundLayer; //ground sprites
    std::vector <sf::Sprite> wallLayer; //all collision block
    sf::Texture spriteSheet; //all textures to set
public:
    MapLoader();
    void loadLayers(std::string mapNumber);
    void draw(sf::RenderWindow &window);
    std::vector <sf::Sprite> showLayer(int number);
};

#endif // MAPLOADER_H
