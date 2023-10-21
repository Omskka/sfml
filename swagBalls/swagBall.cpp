//
// Created by Omskka on 10/19/2023.
//

#include "swagBall.h"

// Constructor and Destructor
swagBall::swagBall(sf::RenderWindow &window, int type) {
    this->type = type;
    this->initShape(window);
}

swagBall::~swagBall() {

}

// Private Functions
void swagBall::initShape(sf::RenderWindow &window) {
    this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
    sf::Color color;
    switch (this->type) {
        case ::DEFAULT:
            color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
            break;

        case ::DAMAGING:
            color = sf::Color::Red;
            this->shape.setOutlineColor(sf::Color::Magenta);
            this->shape.setOutlineThickness(2.f);
            break;

        case ::HEALING:
            color = sf::Color::Green;
            this->shape.setOutlineColor(sf::Color::White);
            this->shape.setOutlineThickness(2.f);
            break;
    }
    this->shape.setFillColor(color);
    this->shape.setPosition(sf::Vector2f(
            static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
            static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)));
}

const int &swagBall::getType() const {
    return (this->type);
}

// Accessors
const sf::CircleShape swagBall::getshape() const {
    return (this->shape);
}

// Update And Render
void swagBall::update() {

}

void swagBall::render(sf::RenderTarget *target) {
    target->draw(this->shape);
}




