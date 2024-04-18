#include "Board.h"

// Constructor initializing the Drawable base and setting the shape size
Board::Board(float width, float height, std::shared_ptr<sf::RenderWindow> win)
    : Drawable(win) {  // Initialize the Drawable part with the window
    shape_.setSize(sf::Vector2f(width, height));
    shape_.setFillColor(sf::Color::Blue);  // Set the fill color to blue
    initializeSquares(200.0f, 100.0f);
}

void Board::draw(float posX, float posY) {
    shape_.setPosition(posX, posY);
    if (window_) {
        window_->draw(shape_);
        for (const auto& square : squares_) {
            window_->draw(square);
        }
    }
}

void Board::initializeSquares(float posX, float posY){
    //squares_.clear();  // Clear previous squares if any
    float x, y;
    float squareWidth = 400 / 11;
    float squareHeight = 400 / 11;
    // Create 9 squares for each side
    for (int side = 0; side < 4; ++side) {
        for (int i = 0; i < 9; ++i) {
            sf::RectangleShape rectangle(sf::Vector2f(squareWidth, squareHeight));
            rectangle.setFillColor(sf::Color::Red);

            if (side % 2 == 0) {  // Top or bottom
                x = posX + squareWidth + i * squareWidth;
                y = side == 0 ? posY : posY + 400 - squareHeight;
            }
            else {  // Left or right
                x = side == 1 ? posX + 400 - squareHeight : posX;
                y = posY + squareWidth + i * squareWidth;
                rectangle.setSize(sf::Vector2f(squareHeight, squareWidth));  // Rotate by swapping width and height
            }

            rectangle.setPosition(x, y);
            squares_.push_back(rectangle);
        }
    }
}