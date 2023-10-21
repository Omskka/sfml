//
// Created by Omskka on 10/19/2023.
//

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "player.h"
#include "swagBall.h"

#ifndef GAME2_GAME_H
#define GAME2_GAME_H

class game {
private:
    sf::VideoMode videoMode;
    sf::RenderWindow *window;
    sf::Event ev;
    sf::Font font;
    sf::Text text;

    int points;
    bool endGame;

    // Create a player
    player player1;

    // Create a container for swagBalls
    std::vector<swagBall> swagBalls;
    float spawnTimerMax;
    float spawnTimer;
    int maxSwagBalls;

    // Private Functions
    void initWindow();

    void initVariables();

public:
    // Constructor And Destructor
    game();

    ~game();

    // Accessors
    const bool &getEndGame();

    const bool getEnd();

    // Modifiers

    // Public Functions
    const bool running();

    void pollEvents();

    void spawnSwagBalls();

    const int randomiseType();

    void updatePlayer();

    void updateCollision();

    void update();

    void updateText();

    void renderText(sf::RenderTarget *target);

    void render();
};


#endif //GAME2_GAME_H
