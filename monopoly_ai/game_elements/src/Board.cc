#include <iostream>
#include "Board.h"

Board::Board(float width, float height, std::shared_ptr<sf::RenderWindow> win)
    : Drawable(win), current_action_(Action::BUY_PROPERTY) {
    current_player_ = 0;
    dice_ = std::make_unique<Dice>(win);
    shape_.setSize(sf::Vector2f(width, height));
    shape_.setFillColor(sf::Color::White);
    initializeSquares(200.0f, 100.0f);
    initializePlayers(4);

    if (!font_.loadFromFile(std::string(BASE_PATH) + "assets/fonts/font.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    // Initialize the text object
    actionText_.setFont(font_);
    actionText_.setCharacterSize(24); // example size
    actionText_.setFillColor(sf::Color::Yellow); // example color
    actionText_.setPosition(10, 10); // example position
    actionText_.setString("TEST TEST");
}

void Board::runRound() {
    dice_->throwDice();
    players_[current_player_]->move(dice_->getValue(), squares_);


    current_player_ = ++current_player_ % 4;
}

void Board::performCurrentAction() {
    if (!isActionAvailable(current_action_)) return;

    auto player = players_[current_player_];
    switch (current_action_) {
    case Action::BUY_PROPERTY:
        // Implement logic to buy property
        std::cout << "Player buys property" << std::endl;
        // Placeholder logic: adjust player's money and mark property as owned// Example cost
        // Assume current square is a property square
        player->decreaseMoney(100);
        break;
    case Action::PAY_RENT:
        // Implement logic to pay rent
        std::cout << "Player pays rent" << std::endl;
        // Placeholder logic: adjust player's money
        player->decreaseMoney(50); // Example rent
        break;
    case Action::BUY_HOUSE:
        // Implement logic to buy house
        std::cout << "Player buys house" << std::endl;
        // Placeholder logic: adjust player's money and add house to property
        player->decreaseMoney(200); // Example house cost
        break;
    case Action::BUY_HOTEL:
        // Implement logic to buy hotel
        std::cout << "Player buys hotel" << std::endl;
        // Placeholder logic: adjust player's money and add hotel to property
        player->decreaseMoney(400); // Example hotel cost
        break;
    case Action::PLEDGE_PROPERTY:
        // Implement logic to pledge property
        std::cout << "Player pledges property" << std::endl;
        // Placeholder logic: mark property as pledged and adjust player's money
        player->increaseMoney(150); // Example pledge value
        break;
    case Action::PAY_TAX:
        // Implement logic to pay tax
        std::cout << "Player pays tax" << std::endl;
        // Placeholder logic: adjust player's money
        player->decreaseMoney(75); // Example tax
        break;
    case Action::REDEEM_PLEDGE:
        // Implement logic to redeem pledged property
        std::cout << "Player redeems pledged property" << std::endl;
        // Placeholder logic: mark property as unpledged and adjust player's money
        player->decreaseMoney(150); // Example redeem cost
        break;
    default:
        std::cout << "Invalid action" << std::endl;
        break;
    }
}

bool Board::isActionAvailable(Action& action) {
    auto player = players_[current_player_];
    auto currentSquare = player->getCurrentSquare();

    switch (action) { // @TODO to implement
    case Action::BUY_PROPERTY:
        // Check if the current square is a property and it can be bought
        // Placeholder check; replace with actual game logic
        return true; // Example: always return true for simplicity
    case Action::PAY_RENT:
        // Check if the player is on a property owned by another player
        return false; // Placeholder
    case Action::BUY_HOUSE:
        // Check if the player owns all properties of a color set and has enough money
        return false; // Placeholder
    case Action::BUY_HOTEL:
        // Check if the player has enough houses to buy a hotel
        return false; // Placeholder
    case Action::PLEDGE_PROPERTY:
        // Check if the player owns the property and it is not already pledged
        return false; // Placeholder
    case Action::PAY_TAX:
        // Check if the current square is a tax square
        return false; // Placeholder
    case Action::REDEEM_PLEDGE:
        // Check if the player has pledged properties that can be redeemed
        return false; // Placeholder
    default:
        return false;
    }
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
        window_->draw(actionText_);
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
