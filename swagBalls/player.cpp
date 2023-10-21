//
// Created by Omskka on 10/19/2023.
//

#include "player.h"

// Constructor And Destructor
player::player(float x, float y) {
    // Set players position
    this->shape.setPosition(x, y);

    initVariables();
    initShape();
}

player::~player() {
    //delete this->shape;
}

// Private Functions
void player::initVariables() {
    this->hpMax = 10;
    this->hp = this->hpMax;
    this->movementSpeed = 5.f;
}

void player::initShape() {
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

// Public Functions
void player::takeDamage(const int damage) {
    if (this->hp > 0) {
        this->hp -= damage;
    }
    if (this->hp < 0) {
        this->hp = 0;
    }
}

void player::gainHealth(const int health) {
    if (this->hp < this->hpMax) {
        this->hp += health;
    }
    if (this->hp >= this->hpMax) {
        this->hp = this->hpMax;
    }
}

// Accessors
const int &player::getHp() const {
    return this->hp;
}

const int &player::getHpMax() const {
    return this->hpMax;
}

const sf::RectangleShape &player::getshape() const {
    return (this->shape);
}

// Update And Render
void player::update(sf::RenderTarget *target) {
    this->updateInput();
    // Window bound collision
    this->updateWindowBounds(target);
}

void player::render(sf::RenderTarget *target) {
    target->draw(this->shape);
}

void player::updateInput() {
    // Keyboard Input
    //Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->shape.move(-1 * this->movementSpeed, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->shape.move(this->movementSpeed, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->shape.move(0.f, (-1 * this->movementSpeed));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->shape.move(0.f, this->movementSpeed);
    }
}

void player::updateWindowBounds(sf::RenderTarget *target) {
    // Left
    if (this->shape.getGlobalBounds().left <= 0.f)
        this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
    // Right
    if (this->shape.getGlobalBounds().left + 50 >= 800)
        this->shape.setPosition(750.f, this->shape.getGlobalBounds().top);
    // Top
    if (this->shape.getGlobalBounds().top <= 0.f)
        this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
    // Bottom
    if (this->shape.getGlobalBounds().top + 50 >= 600.f)
        this->shape.setPosition(this->shape.getGlobalBounds().left, 550.f);
}
