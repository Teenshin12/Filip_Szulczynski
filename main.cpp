#include <SFML/Graphics.hpp>

#include <iostream>

#include "GUIManager.h"
#include "MapLoader.h"

#include "Animation.h"


int main() {
    // variables to set
    sf::Vector2f resolution = {2560,1440};
    sf::Vector2f playerPosition = {16.f, 16.f * 5.f};
    sf::Vector2f cameraOffset = {0, 0};
    int cameraMoveStep = 5;
    int cameraMoveDelay = 10;
    int cameraMaxPosition = 100;
    bool fullscreen = true;
    int characterSize = 100;
    int textPosition = 50;
    float playerSpeed = 2;

    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(resolution.x, resolution.y));
    view1.setViewport(sf::FloatRect(0.f, -0.195f, 1.f, 1.f));
    view1.zoom(0.31);
    sf::View view2(sf::Vector2f(0, 0), sf::Vector2f(3400, 750));
    view2.setViewport(sf::FloatRect( -0.07, 0.858, 0.75, 0.15));

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("background.png");
    sf::Sprite background;
    background.setTexture(backgroundTexture);

    background.setScale(resolution.x/backgroundTexture.getSize().x, resolution.y/backgroundTexture.getSize().y);

    sf::Texture overlayImage;
    overlayImage.loadFromFile("overlay.png");
    sf::Sprite overlay;
    overlay.setTexture(overlayImage);

    overlay.setScale(resolution.x/overlayImage.getSize().x, resolution.y/overlayImage.getSize().y);

    sf::CircleShape playerDot;
    playerDot.setRadius(20);
    playerDot.setOrigin(10,10);
    playerDot.setFillColor(sf::Color::Green);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("player.png");
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);

    Animation playerAnimation(&playerTexture, sf::Vector2u(4,6), 0.3f);

    //creating window
    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "SFML works!");
    if(fullscreen)window.create(sf::VideoMode(resolution.x, resolution.y), "THE GAME", sf::Style::Fullscreen);
    else window.create(sf::VideoMode(resolution.x, resolution.y), "THE GAME");
    window.setFramerateLimit(60);

    //actual scene (menu, game etc.)
    int scene = 0;

    //creating GUIManager
    GUIManager GUIM(resolution, characterSize, textPosition, fullscreen);
    bool loadMenu = true;
    bool loadSettings = false;

    // creating map variable etc.
    MapLoader maploader;
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
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, view1);
                    std::cout << pixelPos.x << " " << pixelPos.y << std:: endl;
                    std::cout << worldPos.x << " " << worldPos.y << std:: endl;
                }
            }
            if (event.type == sf::Event::KeyPressed){
                // Escape = close window
                if (event.key.code == sf::Keyboard::Escape) window.close();
                if (event.key.code == sf::Keyboard::F2) {
                    sf::Texture texture;
                    texture.create(window.getSize().x, window.getSize().y);
                    texture.update(window);
                    if (texture.copyToImage().saveToFile("filename.png"))
                    {
                        std::cout << "screenshot saved to " << "filename.png" << std::endl;
                    }
                }
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
                resolution = {1280, 720};
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
                background.setScale(resolution.x/backgroundTexture.getSize().x*1.01, resolution.y/backgroundTexture.getSize().y*1.01);
                GUIM.setMenu();
            }
            else if (check == 8){
                GUIM.setMenu();
            }
            window.draw(background);
            GUIM.draw(window);
        }

        if(scene == 1){
            window.clear();
            deltaTime = deltaTimeClock.restart().asSeconds(); // restart delta time clock
            cameraStepDelay = cameraStepDelayClock.getElapsedTime().asMilliseconds();

            sf::Vector2f direction = {0, 0};
                 if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction = sf::Vector2f(deltaTime *  70 * playerSpeed, -deltaTime *  70 * playerSpeed);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction = sf::Vector2f(-deltaTime *  70 * playerSpeed, -deltaTime *  70 * playerSpeed);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction = sf::Vector2f(deltaTime *  70 * playerSpeed, deltaTime *  70 * playerSpeed);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction = sf::Vector2f(-deltaTime *  70 * playerSpeed, deltaTime *  70 * playerSpeed);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction = sf::Vector2f(0.f, -deltaTime * 100 * playerSpeed);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction = sf::Vector2f(0.f, deltaTime *  100 * playerSpeed);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction = sf::Vector2f(-deltaTime * 100 * playerSpeed, 0.f);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction = sf::Vector2f(deltaTime *  100 * playerSpeed, 0.f);

            int playerMovement = 0;
            if(direction.x != 0 || direction.y !=0){
                bool collisionX = false;
                bool collisionY = false;
                playerSprite.move(direction);
                if(playerSprite.getPosition().x < -1 || playerSprite.getPosition().x > 1589) collisionX = true;
                if(playerSprite.getPosition().y < -1 || playerSprite.getPosition().y > 19*16+3 ) collisionY = true;

                if(collisionX == false){
                    if(direction.x < 0) playerMovement = 2;
                    else if(direction.x > 0) playerMovement = 1;
                }
                else playerSprite.move(-direction.x, 0);
                if(collisionY == false){
                    if(direction.y > 0) playerMovement = 4;
                    else if(direction.y < 0) playerMovement = 3;
                }
                else playerSprite.move(0, -direction.y);
            }
            playerPosition = playerSprite.getPosition();
            playerDot.setPosition(playerPosition.x - 6, playerPosition.y - 7);



            playerAnimation.Update(playerMovement, deltaTime * 3);
            playerSprite.setTextureRect(playerAnimation.uvRect);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && cameraStepDelay > cameraMoveDelay){
                cameraStepDelay = cameraStepDelayClock.restart().asMilliseconds();
                if(cameraOffset.x >= -cameraMaxPosition)cameraOffset.x -= cameraMoveStep;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && cameraStepDelay > cameraMoveDelay){
                cameraStepDelay = cameraStepDelayClock.restart().asMilliseconds();
                if(cameraOffset.x <= cameraMaxPosition)cameraOffset.x += cameraMoveStep;
            }
            else if (cameraStepDelay > cameraMoveDelay){
                if(cameraOffset.x > 0) cameraOffset.x-=cameraMoveStep;
                else if(cameraOffset.x < 0)cameraOffset.x+=cameraMoveStep;
            }

            view1.setCenter(playerPosition.x + cameraOffset.x, 100);
            window.setView(view1);
            maploader.draw(window);
            window.draw(playerSprite);

            window.setView(view2);
            maploader.draw(window);
            window.draw(playerDot);

            window.setView(window.getDefaultView());
            window.draw(overlay);

            if(levelCounter == 1){maploader.loadLayers("maps/1.txt"); levelCounter++;}
        }

        if(scene == 2){

        }

    window.display();
    } //game loop brackets
    return 0;
} //main brackets
