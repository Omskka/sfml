//
// Created by Omskka on 10/19/2023.
//

#include "game.h"

//Constructor And Destructor
game::game() {
    initVariables();
    initWindow();
}

game::~game() {
    delete this->window;
}

// Private Functions
void game::initWindow() {
    unsigned int windowWidth = 800;
    unsigned int windowHeight = 600;
    this->videoMode = sf::VideoMode(windowWidth, windowHeight);
    this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void game::initVariables() {
    this->endGame = false;
    this->points = 0;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxSwagBalls = 10;

    // Font And Text
    if (!this->font.loadFromFile("../fonts/arcade.ttf"))
        std::cout << "GAME ERROR: COULD NOT LOAD FONTS" << std::endl;
    this->text.setFont(this->font);
    this->text.setCharacterSize(40);
    this->text.setPosition(290, 10);
    this->text.setString("FAILED TO LOAD TEXT!");
}

// Public Functions
const bool game::running() {
    return this->window->isOpen();
}

void game::pollEvents() {
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

const int game::randomiseType() {
    int type = swagBallTypes::DEFAULT;
    int randNum = rand() % 100 + 1;
    if (randNum > 60 && randNum <= 80)
        type = swagBallTypes::DAMAGING;
    else if (randNum > 80 && randNum <= 100)
        type = swagBallTypes::HEALING;
    return (type);
}

void game::spawnSwagBalls() {
    if (this->spawnTimer < this->spawnTimerMax)
        this->spawnTimer += 1.f;
    else {
        if (this->swagBalls.size() < this->maxSwagBalls) {
            this->swagBalls.push_back(swagBall(*this->window, this->randomiseType()));
            this->spawnTimer = 0.f;
        }
    }
}

const bool &game::getEndGame() {
    return (this->endGame);
}

//  Update And Render
void game::update() {
    this->pollEvents();
    this->spawnSwagBalls();
    this->updateCollision();
    this->updateText();
    this->updatePlayer();

}

void game::updateCollision() {
    // Check Collision
    for (int i = 0; i < this->swagBalls.size(); ++i) {
        if (this->player1.getshape().getGlobalBounds().intersects(this->swagBalls[i].getshape().getGlobalBounds())) {
            switch (this->swagBalls[i].getType()) {
                case swagBallTypes::DEFAULT:
                    this->points += 1;
                    break;
                case swagBallTypes::DAMAGING:
                    this->player1.takeDamage(1);
                    break;
                case swagBallTypes::HEALING:
                    this->player1.gainHealth(1);
                    break;
            }
            // Remove the ball
            this->swagBalls.erase(this->swagBalls.begin() + i);
        }
    }
}

void game::render() {
    this->window->clear();
    this->player1.render(this->window);
    for (auto i: this->swagBalls) {
        i.render(this->window);
    }

    // Render Text
    this->renderText(this->window);
    this->window->display();
}

void game::renderText(sf::RenderTarget *target) {
    target->draw(this->text);
}

void game::updateText() {
    std::stringstream str;
    str << "POINTS: " << this->points << "\n"
        << "HEALTH: " << this->player1.getHp() << "/" << this->player1.getHpMax();
    this->text.setString(str.str());
}

void game::updatePlayer() {
    this->player1.update(this->window);

    if (this->player1.getHp() <= 0)
        this->endGame = true;
}
