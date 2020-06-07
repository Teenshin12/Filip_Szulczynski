#include "MapLoader.h"

MapLoader::MapLoader(float scale){
    //set scale
    this->scale = scale;
    //load spritesheet texture
    spriteSheet.loadFromFile("pictures/spritesheet.png");
}

void MapLoader::loadLayers(std::string mapNumber){
    std::fstream map;
    map.open (mapNumber, std::ios::in);
    int map_x, map_y; //size of map
    int pos_x, pos_y; //position in spritesheet

    if( map.good() == true ){
        map >> map_x; // taking x size of the map
        map >> map_y; // taking y size of the map
        for(int i = 0; i < map_x * map_y; i++){
            map >> pos_x; //x position of texture
            map >> pos_y; //x position of texture
            sf::Sprite sprite(spriteSheet, sf::IntRect(17*pos_x, 17*pos_y,16,16)); //17 is a size of texture(16) + space between each texture 1 pixel
            sprite.setScale(scale,scale);
            sprite.setPosition((i % map_x) * 16 * scale, (i/map_x) * 16 * scale); //  i % map_x is actual row, i/map_x is a actual column
            groundLayer.emplace_back(sprite);
        }

        for(int i = 0; i < map_x * map_y; i++){
            map >> pos_x >> pos_y;
            if(pos_x != 0 && pos_y !=5){
                sf::Sprite sprite(spriteSheet, sf::IntRect(0+17*pos_x,0+17*pos_y,16,16)); //17 is a size of texture(16) + space between each texture 1 pixel
                sprite.setScale(scale,scale); //set scale
                sprite.setPosition((i % map_x)*16*scale, (i/map_x)*16*scale); //  i % map_x is actual row, i/map_x is a actual column
                wallLayer.emplace_back(sprite);
            }
        }
    }
    //else std::cout << "error loading map" << std::endl;
    map.close();
}

void MapLoader::draw(sf::RenderWindow &window){
    for(int i = 0; i < (int)groundLayer.size(); i++) window.draw(groundLayer[i]); //draw ground
    for(int i = 0; i < (int)wallLayer.size(); i++) window.draw(wallLayer[i]); // draw walls
}
