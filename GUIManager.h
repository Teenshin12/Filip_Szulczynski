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
bool windowFullscreen = false;


// COLORS //
sf::Color unTouched;
sf::Color Touched;
public:
    GUIManager(sf::Vector2f resolution, int characterSize, int textPosition);
    void setMenu();
    void setSettings();
    int checkLMB(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
};

#endif // GUIMANAGER_H
