#include "BoardSquare.h"
#include <iostream>

BoardSquare::BoardSquare(float width, float height, std::shared_ptr<sf::RenderWindow> win,
    float orientation, const std::string& textContent,
    const sf::Color& fillColor, const std::string& textureFile)
    : Drawable(win), orientation_(orientation), window_(win) {
    shape_.setSize(sf::Vector2f(width, height));
    shape_.setFillColor(fillColor);
    if (!textureFile.empty()) {
        if (!texture_.loadFromFile(std::string(BASE_PATH) + textureFile)) {
            throw std::runtime_error("Failed to load texture: " + textureFile);
        }
        shape_.setTexture(&texture_);
    }
    shape_.setOutlineThickness(2.0f);
    shape_.setOutlineColor(sf::Color::Black);

    //sf::Font font;
    //if (!font.loadFromFile(std::string(BASE_PATH) + "assets/fonts/font.ttf")) {
    //    throw std::runtime_error("Failed to load font");
    //}

    //text_.setFont(font);
    //text_.setString(textContent);
    //text_.setCharacterSize(24);
    //text_.setFillColor(sf::Color::White);
    //text_.setPosition(10, 10);

    //shape_.setRotation(orientation);
    //text_.setRotation(orientation);
}

void BoardSquare::draw() {
    if (window_) {
        window_->draw(shape_);
    }
}

void BoardSquare::setPosition(float x, float y) {
    shape_.setPosition(sf::Vector2f(x, y));
    text_.setPosition(x + 10, y + 10);
}
