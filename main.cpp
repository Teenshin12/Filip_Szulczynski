#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

#include "GUIManager.h"


int main()
{
    // VARIABLES //
    sf::Vector2f resolution = {800,600};
    bool fullscreen = false;
    int characterSize = 100;
    int textPosition = 50;
    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "SFML works!");

    float deltaTime = 0.0f; // Delta time describes the time difference between the previous frame that was drawn and the current frame.
    sf::Clock deltaTimeClock; //deltaTime Offset
    int scene = 0;

    GUIManager GUIM(resolution, characterSize, textPosition);

    bool loadMenu = true;
    bool loadSettings = false;
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                    std::cout << worldPos.x << " " << worldPos.y << std:: endl;
                }
            }
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape) window.close();
            }
        }


        if(scene == 0){
            window.clear();

            if(loadMenu == true){
                GUIM.setMenu();
                loadMenu = false;
            }
            else if(loadSettings == true){
                GUIM.setMenu();
                loadSettings = false;
            }

            int check = GUIM.checkLMB(window);
            if(check == 0){
                scene = 1;
            }
            else if (check == 1){
                GUIM.setSettings();
            }
            else if (check == 2){
                window.close();
            }
            else if (check == 3){
                resolution = {800, 600};
            }
            else if (check == 4){
                resolution = {1920, 1080};
            }
            else if (check == 5){
                resolution = {2560, 1440};
            }
            else if (check == 6){
                fullscreen = not fullscreen;
            }
            else if (check == 7){
                if(fullscreen)window.create(sf::VideoMode(resolution.x, resolution.y, 32), "THE GAME", sf::Style::Fullscreen);
                else window.create(sf::VideoMode(resolution.x, resolution.y, 32), "THE GAME");
                GUIM.setMenu();
            }
            else if (check == 8){
                GUIM.setMenu();
            }

            GUIM.draw(window);
            window.display();
        }

        if(scene == 1){
            deltaTime = deltaTimeClock.restart().asSeconds(); // restart delta time clock

        }

        if(scene == 2){

        }


    }
    return 0;
}
