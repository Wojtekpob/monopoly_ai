#include "BoardSquare.h"
using namespace std;
// Constructor initializing the Drawable base and setting up the square and text
BoardSquare::BoardSquare(float width, float height, std::shared_ptr<sf::RenderWindow> win, float orientation, const std::string& textContent)
    : Drawable(win), orientation_(orientation) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Green);  // Example: Set fill color to green

    // Load a font (ensure the font file is accessible at the given path)
    sf::Font font;
    if (!font.loadFromFile(string(BASE_PATH) + "assets/fonts/font.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    text_.setFont(font);
    text_.setString(textContent);
    text_.setCharacterSize(24); // Set character size
    text_.setFillColor(sf::Color::White); // Set text color to white
    text_.setPosition(10, 10); // Temporary position, adjust based on actual requirements

    // Apply orientation (rotation)
    shape.setRotation(orientation);
    text_.setRotation(orientation);
}

void BoardSquare::draw(float posX, float posY) {
    shape.setPosition(posX, posY);
    text_.setPosition(posX + 10, posY + 10); // Adjust text position relative to the square

    if (window_) {
        window_->draw(shape);
        window_->draw(text_);
    }
}