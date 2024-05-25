#include "Dice.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Constructor definition
Dice::Dice(std::shared_ptr<sf::RenderWindow> window)
    : window_(window), value_(1) {
    loadTextures();
    sprite_.setTexture(textures_[0]); // Initial texture for value 1
    sprite_.setPosition(50.0f, 50.0f); // Set position on screen
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Initialize random generator
}

// Private method to load textures
void Dice::loadTextures() {
    textures_.resize(6);
    for (int i = 0; i < 6; ++i) {
        std::string filename = std::string(BASE_PATH) + "assets/textures/dice" + std::to_string(i + 1) + ".png";
        if (!textures_[i].loadFromFile(filename)) {
            throw std::runtime_error("Failed to load texture: " + filename);
        }
    }
}

// Public method to throw the dice
void Dice::throwDice() {
    value_ = (std::rand() % 6) + 1;
    sprite_.setTexture(textures_[value_ - 1]);
}

// Public method to draw the dice
void Dice::draw() {
    if (window_) {
        window_->draw(sprite_);
    }
}

// Getter for the value
int Dice::getValue() const {
    return value_;
}
