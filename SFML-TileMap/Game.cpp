//
// Created by Omskka on 10/22/2023.
//

#include "Game.h"

// Constructor and destructor
Game::Game() {
    this->initVariables();
    this->getTextureCount();
    this->getImgSize();
    this->readMap();
    this->initTextures();
    this->initWindow();
}

Game::~Game() {
    delete this->window;
}

// Private functions
void Game::initVariables() {
    // Configure tile scale     | Default = 1
    this->scale = 1;

    this->mapX = 0;
    this->mapY = 0;
    this->numX = 0;
    this->numInt = 0;
}

// Get num of textures in '../Textures' directory
void Game::getTextureCount() {
    std::string directoryPath = "../Textures";

    try {
        std::filesystem::directory_iterator it(directoryPath);

        for (const auto &entry: it) {
            this->textureCount++;
        }

    } catch (const std::filesystem::filesystem_error &ex) {
        std::cerr << "GAME ERROR: EMPTY 'TEXTURES' DIRECTORY!" << std::endl;
        this->window->close();
    }
    if (this->textureCount > 1000) {
        std::cerr << "GAMER ERROR: MORE THAN 1000 TEXTURES! ";
        this->window->close();
    }
}

void Game::getImgSize() {
    sf::Image image;
    // Configure path of first image
    if (image.loadFromFile("../Textures/000.png")) {
        this->imgWidth = image.getSize().x;
        this->imgHeight = image.getSize().y;
    } else {
        std::cerr << "GAME ERROR: FAILED TO GET IMAGE SIZE" << std::endl;
        this->window->close();
    }
}

void Game::readMap() {
    // Configure map path
    std::ifstream file("../Maps/map1.txt");

    if (file.is_open()) {
        std::string line;
        std::string content;

        while (std::getline(file, line)) {
            this->mapY += 1;
            content += line;
        }

        file.close();
        // Now, 'content' contains the entire file content as a single line
        this->checkMap(content);
    } else {
        std::cerr << "GAME ERROR: FAILED TO READ MAP!" << std::endl;
        this->window->close();
    }
}

void Game::checkMap(const std::string &map) {
    for (char i: map) {
        if (i == 'X')
            this->numX += 1;
        else if (isdigit(i))
            this->numInt += 1;
    }
    this->mapX = this->numX / this->mapY;

    // Check for wrong layouts
    if (this->numX != numInt / 3) {
        std::cerr << "GAME ERROR(): WRONG MAP LAYOUT!" << std::endl;
        this->window->close();
    } else if (this->numX % this->mapY != 0) {
        std::cerr << "GAME ERROR(): MAP IS NOT RECTANGULAR!" << std::endl;
        this->window->close();
    } else
        getTiles(map);
}

void Game::getTiles(const std::string &map) {
    std::string temp;

    for (char i: map) {
        if (std::isdigit(i)) {
            temp += i;
        } else if (!temp.empty()) {
            int tile = std::stoi(temp);
            if (tile < 0 || tile > this->textureCount) {
                std::cerr << "GAME ERROR(): WRONG MAP LAYOUT!" << std::endl;
                this->window->close();
            }
            this->tiles.push_back(tile);
            temp.clear();
        }
    }
    if (!temp.empty()) {
        int tile = std::stoi(temp);
        tiles.push_back(tile);
    }
}

// Load textures
void Game::initTextures() {
    for (int i = 0; i < this->textureCount; ++i) {
        this->textures[i] = new sf::Texture();
        if (i < 10)
            this->textures[i]->loadFromFile("../Textures/00" + std::to_string(i) + ".png");
        else if (i < 100)
            this->textures[i]->loadFromFile("../Textures/0" + std::to_string(i) + ".png");
        else
            this->textures[i]->loadFromFile("../Textures/" + std::to_string(i) + ".png");
    }
    this->shape.scale(this->scale, this->scale);
}

void Game::initWindow() {
    float windowWidth = (this->scale * this->imgWidth) * this->mapX;
    float windowHeight = (this->scale * this->imgHeight) * this->mapY;
    this->videoMode = sf::VideoMode(windowWidth, windowHeight);
    this->window = new sf::RenderWindow(this->videoMode, "My World", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

// Initialise tile position
void Game::initMap(float x, float y) {
    this->shape.setPosition(x, y);
}

// Public functions
void Game::run() {
    while (this->window->isOpen()) {
        this->update();
        this->render(this->window);
    }
}

void Game::pollEvents() {
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

// Update and render
void Game::update() {
    this->pollEvents();
    this->updateBackground();
}

void Game::updateBackground() {
    // Update Background
}

void Game::render(sf::RenderTarget *target) {
    this->window->clear();
    this->renderBackground(this->window);
    this->window->display();
}

void Game::renderBackground(sf::RenderTarget *target) {
    int tile = 0;
    this->startY = 0;

    this->initMap(this->startX, this->startY);
    for (int i = 0; i < this->mapY; ++i) {
        this->startX = 0;
        this->startY = i * this->shape.getGlobalBounds().height;
        this->initMap(this->startX, this->startY);
        for (int j = 0; j < this->mapX; ++j) {
            this->shape.setTexture(*this->textures[tiles[tile]]);
            target->draw(this->shape);
            tile++;
            this->startX += this->shape.getGlobalBounds().width;
            this->initMap(this->startX, this->startY);
        }
    }
}
