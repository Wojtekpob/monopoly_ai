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

void Board::initializeSquares(float pos_x, float pos_y){
    float x, y;
    int number_of_squares = 11;
    float squareWidth = shape_.getSize().x / number_of_squares; 
    float squareHeight = shape_.getSize().y / number_of_squares;
    std::string textContent = "Sample Text";
    for (int side = 0; side < 4; ++side) {
        for (int i = 0; i < 9; ++i) {

            BoardSquare boardSquare(squareWidth, squareHeight, window_, 0.0f, textContent);


            if (side % 2 == 0) { 
                x = pos_x + squareWidth + i * squareWidth;
                y = side == 0 ? pos_y : pos_y + shape_.getSize().y - squareHeight;
            }
            else {  
                x = side == 1 ? pos_x + shape_.getSize().x - squareHeight : pos_x;
                y = pos_y + squareWidth + i * squareWidth;
                
            }

            boardSquare.setPosition(x, y);
            squares_.push_back(boardSquare);
        }
    }
}


void Board::setPosition(float x, float y) {
    shape_.setPosition(sf::Vector2f(x, y));
}