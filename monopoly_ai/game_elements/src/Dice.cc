#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Dice.h"

Dice::Dice(std::shared_ptr<sf::RenderWindow> window)
    : window_(window), value_(1) {
    loadTextures();
    sprite_.setTexture(textures_[0]);
    sprite_.setPosition(50.0f, 350.0f);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Dice::loadTextures() {
    textures_.resize(6);
    for (int i = 0; i < 6; ++i) {
        std::string filename = std::string(BASE_PATH) + "assets/textures/dice" + std::to_string(i + 1) + ".png";
        if (!textures_[i].loadFromFile(filename)) {
            throw std::runtime_error("Failed to load texture: " + filename);
        }
    }
}

void Dice::throwDice() {
    value_ = (std::rand() % 6) + 1;
    sprite_.setTexture(textures_[value_ - 1]);
}

void Dice::draw() {
    if (window_) {
        window_->draw(sprite_);
    }
}

int Dice::getValue() const {
    return value_;
}
