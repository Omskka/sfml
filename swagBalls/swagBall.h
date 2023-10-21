//
// Created by Omskka on 10/19/2023.
//
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#ifndef GAME2_SWAGBALL_H
#define GAME2_SWAGBALL_H

enum swagBallTypes {
    DEFAULT = 0, DAMAGING, HEALING, NMROFTYPES
};

class swagBall {
private:
    sf::CircleShape shape;
    int type;

    // Private Functions
    void initShape(sf::RenderWindow &window);

public:
    swagBall(sf::RenderWindow &window, int type);

    ~swagBall();

    // Accessor
    const sf::CircleShape getshape() const;

    const int &getType() const;

    // Public Functions
    void update();

    void render(sf::RenderTarget *target);
};


#endif //GAME2_SWAGBALL_H
