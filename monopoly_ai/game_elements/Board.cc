#include <iostream>
#include "Board.h"

Board::Board(float width, float height, std::shared_ptr<sf::RenderWindow> win)
    : Drawable(win) {
    current_player_ = 0;
    dice_ = std::make_unique<Dice>(win);
    shape_.setSize(sf::Vector2f(width, height));
    shape_.setFillColor(sf::Color::White);
    initializeSquares(200.0f, 100.0f);
    initializePlayers(4);
}

void Board::runRound() {
    dice_->throwDice();
    players_[current_player_]->move(dice_->getValue(), squares_);

    current_player_ = ++current_player_ % 4;
}

void Board::draw() {
    if (window_) {
        window_->draw(shape_);
        for (auto& square : squares_) {
            square->draw();
        }
        for (auto& player : players_) {
            player->draw();
        }
        dice_->draw();
    }
}

void Board::initializePlayers(int players=1) {
    std::vector<sf::Vector2f> position_biases = {
        sf::Vector2f(7.0f, 7.0f),
        sf::Vector2f(27.0f, 7.0f),
        sf::Vector2f(7.0f, 27.0f),
        sf::Vector2f(27.0f, 27.0f)
    };
    for (int i = 0; i < players; i++) {
        players_.push_back(std::make_shared<Player>(window_, squares_[0], position_biases[i], i));
    }
}

void Board::initializeSquares(float pos_x, float pos_y) {
   
    float x, y;
    int number_of_squares = 11;
    float squareWidth = shape_.getSize().x / number_of_squares;
    float squareHeight = shape_.getSize().y / number_of_squares;
    squares_.resize((number_of_squares - 1) * 4);
    std::vector<std::pair<std::string, std::string>> specialTiles = {
        {"GO", "assets/textures/start.jpg"},
        {"Jail", "assets/textures/jail.jpg"},
        {"Free Parking", "assets/textures/parking.png"},
        {"Go To Jail", "assets/textures/go_to_jail.png"}
    };

    std::vector<sf::Color> propertyColors = {
        sf::Color::White,
        sf::Color::Yellow,
        sf::Color::Magenta,
        sf::Color::Yellow,
        sf::Color::Magenta,
        sf::Color::Magenta,
        sf::Color::Red,
        sf::Color::Magenta,
        sf::Color::Red,
        sf::Color::Red,
        sf::Color::White,
        sf::Color::Blue,
        sf::Color::Magenta,
        sf::Color::Blue,
        sf::Color::Blue,
        sf::Color::Magenta,
        sf::Color(255, 165, 0),
        sf::Color::Magenta,
        sf::Color(255, 165, 0),
        sf::Color(255, 165, 0),
        sf::Color::White,
        sf::Color::Green,
        sf::Color::Magenta,
        sf::Color::Green,
        sf::Color::Green,
        sf::Color::Magenta,
        sf::Color(128, 0, 128),
        sf::Color(128, 0, 128),
        sf::Color::Magenta,
        sf::Color(128, 0, 128),
        sf::Color::White,
        sf::Color(165, 42, 42),
        sf::Color(165, 42, 42),
        sf::Color::Magenta,
        sf::Color(165, 42, 42),
        sf::Color::Magenta,
        sf::Color::Magenta,
        sf::Color::Black,
        sf::Color::Magenta,
        sf::Color::Black

        //sf::Color(165, 42, 42),    // Brown
        //sf::Color(165, 42, 42),    // Brown
        //sf::Color(75, 155, 195),   // Light Blue
        //sf::Color(75, 155, 195),   // Light Blue
        //sf::Color(75, 155, 195),   // Light Blue
        //sf::Color(199, 0, 144),    // Pink
        //sf::Color(199, 0, 144),    // Pink
        //sf::Color(199, 0, 144),    // Pink
        //sf::Color(255, 165, 0),    // Orange
        //sf::Color(255, 165, 0),    // Orange
        //sf::Color(255, 165, 0),    // Orange
        //sf::Color(255, 0, 0),      // Red
        //sf::Color(255, 0, 0),      // Red
        //sf::Color(255, 0, 0),      // Red
        //sf::Color(255, 255, 0),    // Yellow
        //sf::Color(255, 255, 0),    // Yellow
        //sf::Color(255, 255, 0),    // Yellow
        //sf::Color(0, 128, 0),      // Green
        //sf::Color(0, 128, 0),      // Green
        //sf::Color(0, 128, 0),      // Green
        //sf::Color(0, 0, 255),      // Dark Blue
        //sf::Color(0, 0, 255)       // Dark Blue
    };

    int specialTileIndex = 0;
    int propertyColorIndex = 0;
    int counter = 0;
    for (int i = 0; i < number_of_squares; ++i) {
        for (int j = 0; j < number_of_squares; ++j) {
            if (i > 0 && i < number_of_squares - 1 && j > 0 && j < number_of_squares - 1) {
                // Skip the center 9x9 area
                continue;
            }

            std::string textContent = "Property";
            //sf::Color fillColor = propertyColors[propertyColorIndex];
            std::string textureFile = "";


            if ((i == 0 && j == 0) || (i == 0 && j == number_of_squares - 1) ||
                (i == number_of_squares - 1 && j == 0) || (i == number_of_squares - 1 && j == number_of_squares - 1)) {
                textContent = specialTiles[specialTileIndex].first;
                textureFile = specialTiles[specialTileIndex].second;
                //fillColor = sf::Color::White;
                specialTileIndex++;
            }
            else {
                propertyColorIndex++;
            }

            auto boardSquare = std::make_shared<BoardSquare>(squareWidth, squareHeight, window_, 0.0f, textContent, sf::Color::White, textureFile);

            x = pos_x + j * squareWidth;
            y = pos_y + i * squareHeight;
            boardSquare->setPosition(x, y);
            if (counter <= 10) {
                squares_[counter] = boardSquare;
            }
            else if (counter < 30) {
                if (counter % 2 == 1) {
                    squares_[- 0.5 * counter + 44.5] = boardSquare;
                }
                else squares_[0.5 * counter + 5] = boardSquare;
            }
            else squares_[59 - counter] = boardSquare;
            ++counter;
            if (!((i == 0 && j == 0) || (i == 0 && j == number_of_squares - 1) ||
                (i == number_of_squares - 1 && j == 0) || (i == number_of_squares - 1 && j == number_of_squares - 1))) {
                propertyColorIndex = (propertyColorIndex + 1) % propertyColors.size();
            }
        }
    }
    for (int i = 0; i < squares_.size(); i++) {
        squares_[i]->setColor(propertyColors[i]);
    }
}

void Board::setPosition(float x, float y) {
    shape_.setPosition(sf::Vector2f(x, y));
}
