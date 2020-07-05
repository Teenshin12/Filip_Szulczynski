#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <SFML/Graphics.hpp>

#include <vector>

class GUIManager{
private:
std::vector <sf::Text> texts;
std::vector <sf::Vector2f> positions;
sf::Font font;
sf::Vector2f resolution;
sf::Vector2f resToSet;
int characterSize;
int textPosition;
int scene = 0;
bool mouseButtonReleased = true;
bool fullscreen = false;


// COLORS //
sf::Color unTouched;
sf::Color Touched;
public:
GUIManager(sf::Vector2f resolution = {2560,1440}, int characterSize = 100, int textPosition = 50, bool fullscreen = true);
    void setMenu();
    void setSettings();
    void setTheEnd();
    int checkLMB(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
};

#endif // GUIMANAGER_H
