//
// Created by Omskka on 10/22/2023.
//


#ifndef MYWORLD_GAME_H
#define MYWORLD_GAME_H

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Game {
private:
    // Window
    sf::VideoMode videoMode;
    sf::RenderWindow *window;
    sf::Event ev;

    // map
    int mapX;
    int mapY;
    int numX;
    int numInt;
    int textureCount;
    float startX;
    float startY;
    float scale;
    unsigned int imgWidth;
    unsigned int imgHeight;
    sf::Sprite shape;
    std::map<int, sf::Texture *> textures;
    std::vector<int> tiles;
    //std::vector<Bullet*> bullets;

    // Private functions
    void initWindow();

    void initVariables();

    void getImgSize();

    void getTextureCount();

    void initTextures();

    void initMap(float x, float y);

    void readMap();

    void getTiles(const std::string &map);

    void checkMap(const std::string &map);

public:
    // Constructor and destructor
    Game();

    ~Game();

    // Public functions
    void run();

    void pollEvents();

    // Update and render
    void update();

    void render(sf::RenderTarget *target);

    void updateBackground();

    void renderBackground(sf::RenderTarget *target);
};


#endif //MYWORLD_GAME_H
