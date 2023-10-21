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

#ifndef GAME2_PLAYER_H
#define GAME2_PLAYER_H


class player {
private:
    sf::RectangleShape shape;

    int hp;
    int hpMax;
    float movementSpeed;

    // Private Functions
    void initVariables();

    void initShape();

public:
    // Constructor And Destructor
    player(float x = 0.f, float y = 0.f);

    ~player();

    // Accessors
    const sf::RectangleShape &getshape() const;

    const int &getHp() const;

    const int &getHpMax() const;

    // Public Functions
    void takeDamage(const int damage);

    void gainHealth(const int health);

    void updateInput();

    void updateWindowBounds(sf::RenderTarget *target);

    void update(sf::RenderTarget *target);

    void render(sf::RenderTarget *target);
};


#endif //GAME2_PLAYER_H
