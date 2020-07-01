#include <SFML/Graphics.hpp>

#include <iostream>

#include "GUIManager.h"
#include "MapLoader.h"

#include "PlayerCharacter.h"
#include "Skeleton.h"
#include "GameObjects.h"


int main() {
    srand( time( NULL ) );
    // variables to set
    sf::Vector2f resolution = {2560,1440}; //ustawienia rozdzielczosci
    sf::Vector2f cameraOffset = {0, 0}; //zmiana pozycji kamery
    int cameraMoveStep = 5; //krok ruchu kamery
    int cameraMoveDelay = 10; //czas pomiedzy krokami kamery
    int cameraMaxPosition = 100; //maksymalne wychylenie kamery
    bool fullscreen = true; // czy pelny ekran?
    int characterSize = 100; //rozmiar tekstu
    int textPosition = 50; //poczatkowa pozycja tekstu
    float playerSpeed = 6; //predkosc gracza
    int numberOfSkeletons = 100;
    MapLoader maploader;
    int levelCounter = 0;
    bool loaded = false;

    //Ustawienia rzutow
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(resolution.x, resolution.y));
    view1.setViewport(sf::FloatRect(0.f, -0.195f, 1.f, 1.f));
    view1.zoom(0.31);
    sf::View view2(sf::Vector2f(0, 0), sf::Vector2f(3400, 750));
    view2.setViewport(sf::FloatRect( -0.07, 0.858, 0.75, 0.15));

    //Ladowanie tekstury tla
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("background.png");
    //Tworzenie sprite'a tla
    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setScale(resolution.x/backgroundTexture.getSize().x, resolution.y/backgroundTexture.getSize().y);

    //texktura nakladki na gre
    sf::Texture overlayImage;
    overlayImage.loadFromFile("overlay.png");
    //sprite nakladki
    sf::Sprite overlay;
    overlay.setTexture(overlayImage);
    overlay.setScale(resolution.x/overlayImage.getSize().x, resolution.y/overlayImage.getSize().y);

    //Ladowanie mapy
    if(loaded == false){
        maploader.loadLayers("maps/1.txt"); //1600x320 rozmiar mapy w pikselach
        levelCounter = 1;
    }

    //Nastepny poziom
    sf::CircleShape nextLevel;
    nextLevel.setRadius(10);
    nextLevel.setOrigin(10,10);
    nextLevel.setPosition(1550,150);
    nextLevel.setFillColor(sf::Color::Cyan);

    //vector obiektow typu gameObject
    std::vector<std::unique_ptr<GameObjects>> GO;

    //Dodanie gracza na pierwsza pozycje vectora
    GO.emplace_back(std::make_unique<PlayerCharacter>());
    //Tworzenie wskaznika na gracza
    PlayerCharacter *player = dynamic_cast<PlayerCharacter *>(GO[0].get());

    //Dodanie "numberOfSkeletons" szkieletow
    for(int i = 0; i < numberOfSkeletons; i++){
        float rand1 =( std::rand() % 10 ) + 10;
        float rand2 =( std::rand() % 1334 ) + 116;
        float rand3 =( std::rand() % 304 ) + 16;
        GO.emplace_back(std::make_unique<Skeleton>(rand1, sf::Vector2f(rand2,rand3)));
    }
    player->loadWalls(maploader.showLayer(0));


    //tworzenie okna
    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "SFML works!");
    if(fullscreen)window.create(sf::VideoMode(resolution.x, resolution.y), "THE GAME", sf::Style::Fullscreen);
    else window.create(sf::VideoMode(resolution.x, resolution.y), "THE GAME");
    window.setFramerateLimit(60);

    //aktualna scena (menu, gra (odpowiednia cyfra))
    int scene = 0;

    //tworzenie GUIManager
    GUIManager GUIM(resolution, characterSize, textPosition, fullscreen);
    bool loadMenu = true;
    bool loadSettings = false;


    // clocks
    sf::Clock deltaTimeClock;
    float deltaTime = 0.0f; // deltaTime - czas pomiedzy poszczegolnymi klatkami w grze

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

        //scena 0
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

        //scena 1
        if(scene == 1){
            window.clear(); //czyszczenie okna
            deltaTime = deltaTimeClock.restart().asSeconds(); // restart zegara deltaTime
            //Sekcja aktualizowania wartosci deltaTime w obiektach gry
            for(size_t i = 0; i < GO.size(); i++){
                GameObjects *someGameObject = dynamic_cast<GameObjects *>(GO[i].get());
                someGameObject->updateDeltaTime(deltaTime);
            }
            cameraStepDelay = cameraStepDelayClock.getElapsedTime().asMilliseconds();

            sf::Vector2f direction = {0, 0};
                 if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction = sf::Vector2f(deltaTime *  70 * playerSpeed, -deltaTime *  70 * playerSpeed);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction = sf::Vector2f(-deltaTime *  70 * playerSpeed, -deltaTime *  70 * playerSpeed);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction = sf::Vector2f(0.f, -deltaTime * 100 * playerSpeed);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction = sf::Vector2f(deltaTime *  70 * playerSpeed, deltaTime *  70 * playerSpeed);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction = sf::Vector2f(-deltaTime *  70 * playerSpeed, deltaTime *  70 * playerSpeed);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction = sf::Vector2f(0.f, deltaTime *  100 * playerSpeed);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction = sf::Vector2f(-deltaTime * 100 * playerSpeed, 0.f);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction = sf::Vector2f(deltaTime *  100 * playerSpeed, 0.f);


            //Sekcja ruchu w obiktach gry
            for(size_t i = 0; i < GO.size(); i++){
                GameObjects *someGameObject = dynamic_cast<GameObjects *>(GO[i].get());
                if(i == 0) someGameObject->move(direction);
                else someGameObject->move(player->returnPosition());
            }

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

            //ladowanie nowych poziomow gdy gracz dojdzie do kranca mapy
            if(player->returnSprite().getGlobalBounds().intersects(nextLevel.getGlobalBounds())) {levelCounter++; player->setPosition({16,150}); loaded = false; }
            if(levelCounter == 2 && loaded == false){maploader.loadLayers("maps/2.txt"); player->loadWalls(maploader.showLayer(0)); player->loadWalls(maploader.showLayer(0)); loaded = true; }
            else if(levelCounter == 3 && loaded == false){maploader.loadLayers("maps/3.txt"); player->loadWalls(maploader.showLayer(0)); player->loadWalls(maploader.showLayer(0)); loaded = true; }
            else if(levelCounter == 4 && loaded == false){maploader.loadLayers("maps/3.txt"); player->loadWalls(maploader.showLayer(0)); player->loadWalls(maploader.showLayer(0)); loaded = true; }
            else if(levelCounter == 5 && loaded == false){maploader.loadLayers("maps/3.txt"); player->loadWalls(maploader.showLayer(0)); player->loadWalls(maploader.showLayer(0)); loaded = true; }

            view1.setCenter(player->returnPosition().x + cameraOffset.x, 100);
            window.setView(view1);
            maploader.draw(window);
            window.draw(nextLevel);
            for(size_t i = 0; i < GO.size(); i++){
                GameObjects *someGameObject = dynamic_cast<GameObjects *>(GO[i].get());
                someGameObject->drawGame(window);
            }

            window.setView(view2);
            maploader.draw(window);
            window.draw(nextLevel);
            for(size_t i = 0; i < GO.size(); i++){
                GameObjects *someGameObject = dynamic_cast<GameObjects *>(GO[i].get());
                someGameObject->drawMinimap(window);
            }

            window.setView(window.getDefaultView());
            window.draw(overlay);
        }

    window.display();
    } //nawias petli gry
    return 0;
} //nawias main
