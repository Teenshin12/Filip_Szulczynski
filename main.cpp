#include <SFML/Graphics.hpp>

#include <iostream>

#include "GUIManager.h"
#include "MapLoader.h"


int main() {
    // variables to set
    int scale = 3;
    sf::Vector2f resolution = {1920,1080};
    sf::Vector2f playerPosition = {16.f * scale, 16.f * 5.f * scale};
    sf::Vector2f cameraOffset = {0, 0};
    int cameraMoveStep = 5;
    int cameraMoveDelay = 10;
    int cameraMaxPosition = 100;
    bool fullscreen = false;
    int characterSize = 100;
    int textPosition = 50;

    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(resolution.x, resolution.y));
    view1.setViewport(sf::FloatRect(0.f, -0.20f, 1.f, 1.f));
    sf::View view2(sf::Vector2f(0, 0), sf::Vector2f(6400, 640));
    view2.setViewport(sf::FloatRect(-0.25, 0.88, 1, 0.1f));

    sf::Texture overlayImage;
    overlayImage.loadFromFile("overlay.png");
    sf::Sprite overlay;
    overlay.setTexture(overlayImage);

    overlay.setScale(resolution.x/overlayImage.getSize().x, resolution.y/overlayImage.getSize().y);


    //creating window
    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "SFML works!");//, sf::Style::Fullscreen

    //actual scene (menu, game etc.)
    int scene = 0;

    //creating GUIManager

    GUIManager GUIM(resolution, characterSize, textPosition);
    bool loadMenu = true;
    bool loadSettings = false;

    // creating map variable etc.
    MapLoader maploader(scale);
    int levelCounter = 1;

    // clocks
    sf::Clock deltaTimeClock; //deltaTime Offset
    float deltaTime = 0.0f; // Delta time describes the time difference between the previous frame that was drawn and the current frame.
    sf::Clock cameraStepDelayClock;
    float cameraStepDelay = 0.0f;
    cameraStepDelay = cameraStepDelayClock.restart().asMilliseconds();
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if(event.type == sf::Event::MouseButtonPressed){
                //Check mouse position on left click
                if(event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                    std::cout << pixelPos.x << " " << pixelPos.y << std:: endl;
                    std::cout << worldPos.x << " " << worldPos.y << std:: endl;
                }
            }
            if (event.type == sf::Event::KeyPressed){
                // Escape = close window
                if (event.key.code == sf::Keyboard::Escape) window.close();
                if (event.key.code == sf::Keyboard::Space) cameraOffset.x = 0;
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
                overlay.setScale(resolution.x/overlayImage.getSize().x, resolution.y/overlayImage.getSize().y);
                GUIM.setMenu();
            }
            else if (check == 8){
                GUIM.setMenu();
            }
            GUIM.draw(window);
        }

        if(scene == 1){
            window.clear();
            deltaTime = deltaTimeClock.restart().asSeconds(); // restart delta time clock
            cameraStepDelay = cameraStepDelayClock.getElapsedTime().asMilliseconds();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && cameraStepDelay > cameraMoveDelay){
                cameraStepDelay = cameraStepDelayClock.restart().asMilliseconds();
                if(cameraOffset.x >= -cameraMaxPosition)cameraOffset.x -= cameraMoveStep;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && cameraStepDelay > cameraMoveDelay){
                cameraStepDelay = cameraStepDelayClock.restart().asMilliseconds();
                if(cameraOffset.x <= cameraMaxPosition)cameraOffset.x += cameraMoveStep;
            }
            view1.setCenter(playerPosition + cameraOffset);
            if(levelCounter == 1){maploader.loadLayers("maps/1.txt"); levelCounter++;}
            window.setView(view1);
            maploader.draw(window);
            window.setView(view2);
            maploader.draw(window);
            window.setView(window.getDefaultView());
            window.draw(overlay);
        }

        if(scene == 2){

        }

    window.display();
    } //game loop brackets
    return 0;
} //main brackets
