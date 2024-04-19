#include "Board.h"

Board::Board(float width, float height, std::shared_ptr<sf::RenderWindow> win)
    : Drawable(win) {
    shape_.setSize(sf::Vector2f(width, height));
    shape_.setFillColor(sf::Color::Blue); 
    initializeSquares(200.0f, 100.0f);
}

void Board::draw() {
    if (window_) {
        window_->draw(shape_);
        for (auto& square : squares_) {
            square.draw();
        }
    }
}

void Board::initializeSquares(float posX, float posY){
    float x, y;
    float squareWidth = 400 / 11;
    float squareHeight = 400 / 11;
    std::string textContent = "Sample Text";
    for (int side = 0; side < 4; ++side) {
        for (int i = 0; i < 9; ++i) {

            BoardSquare boardSquare(squareWidth, squareHeight, window_, 0.0f, textContent);


            if (side % 2 == 0) { 
                x = posX + squareWidth + i * squareWidth;
                y = side == 0 ? posY : posY + 400 - squareHeight;
            }
            else {  
                x = side == 1 ? posX + 400 - squareHeight : posX;
                y = posY + squareWidth + i * squareWidth;
                
            }

            boardSquare.setPosition(x, y);
            squares_.push_back(boardSquare);
        }
    }
}


void Board::setPosition(float x, float y) {
    shape_.setPosition(sf::Vector2f(x, y));
}