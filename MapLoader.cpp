#include "MapLoader.h"

MapLoader::MapLoader(){
    //load spritesheet texture
    spriteSheet.loadFromFile("pictures/spritesheet.png");
}

void MapLoader::loadLayers(std::string mapNumber){
    groundLayer.clear();
    wallLayer.clear();
    std::fstream map;
    map.open (mapNumber, std::ios::in);
    sf::Vector2i mapSize;
    sf::Vector2i posSpriteSheet;

    if( map.good() == true ){
        map >> mapSize.x; // taking x size of the map
        map >> mapSize.y; // taking y size of the map
        for(int i = 0; i < mapSize.x * mapSize.y; i++){
            map >> posSpriteSheet.x; //x position of texture
            map >> posSpriteSheet.y; //x position of texture
            if(posSpriteSheet.x != 6 && posSpriteSheet.y !=6){
                sf::Sprite sprite(spriteSheet, sf::IntRect(17*posSpriteSheet.x, 17*posSpriteSheet.y,16,16)); //17 is a size of texture(16) + space between each texture 1 pixel
                sprite.setPosition((i % mapSize.x) * 16, (i/mapSize.x) * 16); //  i % map_x is actual row, i/map_x is a actual column
                groundLayer.emplace_back(sprite);
            }
        }

        for(int i = 0; i < mapSize.x * mapSize.y; i++){
            map >> posSpriteSheet.x >> posSpriteSheet.y;
            if(posSpriteSheet.x != 6 && posSpriteSheet.y !=6){
                sf::Sprite sprite(spriteSheet, sf::IntRect(0+17*posSpriteSheet.x,0+17*posSpriteSheet.y,16,16)); //17 is a size of texture(16) + space between each texture 1 pixel
                sprite.setPosition((i % mapSize.x)*16, (i/mapSize.x)*16); //  i % map_x is actual row, i/map_x is a actual column
                wallLayer.emplace_back(sprite);
            }
        }
    }
    //else std::cout << "error loading map" << std::endl;
    map.close();
}

void MapLoader::draw(sf::RenderWindow &window){
    for(size_t i = 0; i < groundLayer.size(); i++) window.draw(groundLayer[i]); //draw ground
    for(size_t i = 0; i < wallLayer.size(); i++) window.draw(wallLayer[i]); // draw walls
}

std::vector <sf::Sprite> MapLoader::showLayer(int number){
    if(number == 0)return wallLayer;
    else return groundLayer;
}
