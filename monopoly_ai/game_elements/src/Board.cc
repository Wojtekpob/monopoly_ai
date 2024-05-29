#include <iostream>
#include "Board.h"

Board::Board(float width, float height, std::shared_ptr<sf::RenderWindow> win)
    : Drawable(win), current_action_(Action::BUY_PROPERTY), current_player_(0), fieldLoader_(), dice_tossed_(false), selected_property_(5) {
    dice_ = std::make_unique<Dice>(win);
    shape_.setSize(sf::Vector2f(width, height));
    shape_.setFillColor(sf::Color::White);
    initializeSquares(200.0f, 100.0f);
    initializePlayers(4);
    setActionAvailability();

    if (!font_.loadFromFile(std::string(BASE_PATH) + "assets/fonts/font.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    actionText_.setFont(font_);
    actionText_.setCharacterSize(24); 
    actionText_.setPosition(610.0f, 5.0f); 

    playerText_.setFont(font_);
    playerText_.setCharacterSize(24);

    fieldsText_.setFont(font_);
    fieldsText_.setCharacterSize(18);
    fieldsText_.setPosition(800.0f, 5.0f);

    updatePlayerText();
}

void Board::runRound() {
    dice_->throwDice();
    getCurrentPlayer()->move(dice_->getValue(), squares_);
    dice_tossed_ = true;
    setActionAvailability();
    //nextPlayer();
}

std::shared_ptr<Player> Board::getCurrentPlayer() {
    return players_[current_player_];
}

void Board::performCurrentAction() {
    if (!action_available_) return;

    auto player = getCurrentPlayer();
    auto currentSquare = player->getCurrentSquare();
    currentSquare->actionField_->invokeAction(player);
    setActionAvailability();
    //switch (current_action_) {
    //case Action::BUY_PROPERTY:
    //    // Implement logic to buy property
    //    std::cout << "Player buys property" << std::endl;
    //    // Placeholder logic: adjust player's money and mark property as owned// Example cost
    //    // Assume current square is a property square
    //    player->decreaseMoney(100);
    //    break;
    //case Action::PAY_RENT:
    //    // Implement logic to pay rent
    //    std::cout << "Player pays rent" << std::endl;
    //    // Placeholder logic: adjust player's money
    //    player->decreaseMoney(50); // Example rent
    //    break;
    //case Action::BUY_HOUSE:
    //    // Implement logic to buy house
    //    std::cout << "Player buys house" << std::endl;
    //    // Placeholder logic: adjust player's money and add house to property
    //    player->decreaseMoney(200); // Example house cost
    //    break;
    //case Action::BUY_HOTEL:
    //    // Implement logic to buy hotel
    //    std::cout << "Player buys hotel" << std::endl;
    //    // Placeholder logic: adjust player's money and add hotel to property
    //    player->decreaseMoney(400); // Example hotel cost
    //    break;
    //case Action::PLEDGE_PROPERTY:
    //    // Implement logic to pledge property
    //    std::cout << "Player pledges property" << std::endl;
    //    // Placeholder logic: mark property as pledged and adjust player's money
    //    player->increaseMoney(150); // Example pledge value
    //    break;
    //case Action::PAY_TAX:
    //    // Implement logic to pay tax
    //    std::cout << "Player pays tax" << std::endl;
    //    // Placeholder logic: adjust player's money
    //    player->decreaseMoney(75); // Example tax
    //    break;
    //case Action::REDEEM_PLEDGE:
    //    // Implement logic to redeem pledged property
    //    std::cout << "Player redeems pledged property" << std::endl;
    //    // Placeholder logic: mark property as unpledged and adjust player's money
    //    player->decreaseMoney(150); // Example redeem cost
    //    break;
    //default:
    //    std::cout << "Invalid action" << std::endl;
    //    break;
    //}
}

void Board::setActionAvailability() {
    action_available_ = isActionAvailable(current_action_);
}

bool Board::isActionAvailable(Action& action) {
    if (action == Action::PLEDGE_PROPERTY || action == Action::REDEEM_PLEDGE) return true;
    auto player = getCurrentPlayer();
    auto currentSquare = player->getCurrentSquare();
    auto a = currentSquare->actionField_->isActionAvailable(player, action);
    return a;
    //switch (action) { // @TODO to implement
    //case Action::BUY_PROPERTY:
    //    // Check if the current square is a property and it can be bought
    //    // Placeholder check; replace with actual game logic
    //    return true; // Example: always return true for simplicity
    //case Action::PAY_RENT:
    //    // Check if the player is on a property owned by another player
    //    return false; // Placeholder
    //case Action::BUY_HOUSE:
    //    // Check if the player owns all properties of a color set and has enough money
    //    return false; // Placeholder
    //case Action::BUY_HOTEL:
    //    // Check if the player has enough houses to buy a hotel
    //    return true; // Placeholder
    //case Action::PLEDGE_PROPERTY:
    //    // Check if the player owns the property and it is not already pledged
    //    return false; // Placeholder
    //case Action::PAY_TAX:
    //    // Check if the current square is a tax square
    //    return false; // Placeholder
    //case Action::REDEEM_PLEDGE:
    //    // Check if the player has pledged properties that can be redeemed
    //    return false; // Placeholder
    //default:
    //    return false;
    //}
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
        drawAction();
        drawLeaderBoard();
        window_->draw(playerText_);
        drawSquaresDescription();
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
    std::vector<std::shared_ptr<ActionField>> fields = fieldLoader_.loadFields(std::string(BASE_PATH) + "assets/fields/fields.json");
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
        }
    }
    for (int i = 0; i < squares_.size(); i++) {
        squares_[i]->setColor(fields[i]->color_);
        squares_[i]->setActionField(fields[i]);
        std::cout << fields[i]->name_ << std::endl;
    }
   
}

void Board::setPosition(float x, float y) {
    shape_.setPosition(sf::Vector2f(x, y));
}

void Board::nextPlayer() {
    getCurrentPlayer()->getCurrentSquare()->actionField_->nextRound();
    current_player_ = (current_player_ + 1) % players_.size();
    current_action_ = Action::BUY_PROPERTY;
    setActionAvailability();
    updatePlayerText();
    dice_tossed_ = false;
}

void Board::drawSquaresDescription() {
    std::string str;
    for (auto square : squares_) {

        fieldsText_.setPosition(fieldsText_.getPosition() + sf::Vector2f(0.0, 20.0));
        fieldsText_.setString(square->actionField_->name_);
        fieldsText_.setColor(square->actionField_->color_);
        if (selected_property_ == square->actionField_->getId()) {
            sf::RectangleShape highlightRect;
            highlightRect.setSize(sf::Vector2f(fieldsText_.getLocalBounds().width, fieldsText_.getLocalBounds().height));
            highlightRect.setFillColor(sf::Color::Yellow);
            highlightRect.setPosition(fieldsText_.getPosition());
            window_->draw(highlightRect);
        }
        window_->draw(fieldsText_);
    }
    fieldsText_.setPosition(950.0f, 5.0f);
}

void Board::drawAction() {
    if (action_available_) {
        actionText_.setFillColor(sf::Color::Green);
    }
    else {
        actionText_.setFillColor(sf::Color(105, 105, 105));
    }
    std::string str;
    
    switch (current_action_) {
    case Action::BUY_PROPERTY:
        str = "ACTION: BUY_PROPERTY";
        break;
    case Action::PAY_RENT:
        str = "ACTION: PAY_RENT";
        break;
    case Action::BUY_HOUSE:
        str = "ACTION: BUY_HOUSE";
        break;
    case Action::BUY_HOTEL:
        str = "ACTION: BUY_HOTEL";
        break;
    case Action::PLEDGE_PROPERTY:
        str = "ACTION: PLEDGE_PROPERTY";
        break;
    case Action::PAY_TAX:
        str = "ACTION: PAY_TAX";
        break;
    case Action::REDEEM_PLEDGE:
        str = "ACTION: REDEEM_PLEDGE";
        break;
    default:
        str = "Unknown Action";
        break;
    }
    actionText_.setString(str + "\n" + getCurrentPlayer()->getCurrentSquare()->actionField_->getStr(Action::REDEEM_PLEDGE));
    window_->draw(actionText_);
}



void Board::incrementAction() {
    ++current_action_;
    setActionAvailability();
}

void Board::decrementAction() {
    --current_action_;
    setActionAvailability();
}

void Board::updatePlayerText() {
    std::string money = std::to_string(getCurrentPlayer()->getMoney());
    playerText_.setString("Player " + std::to_string(current_player_) + "\t\t\t" + money + " $");
}

void Board::drawLeaderBoard() {
    for (int i = 0; i < players_.size(); ++i) {
        
        std::string money = std::to_string(players_[i]->getMoney());
        playerText_.setString("Player " + std::to_string(i) + "\t\t\t" + money + " $");
        if (i == current_player_) playerText_.setFillColor(sf::Color::Green);
        else playerText_.setFillColor(sf::Color::White);
        playerText_.setPosition(10.0f, (i) * 20.0f);
        window_->draw(playerText_);
    }
}

std::vector<std::shared_ptr<Property>> Board::getPlayersProperties() {
    auto player = getCurrentPlayer();
    std::vector<std::shared_ptr<Property>> playerProperties;

    for (int propertyId : player->getProperties()) {
        if (propertyId >= 0 && propertyId < squares_.size()) {
            std::shared_ptr<ActionField> actionField = squares_[propertyId]->actionField_;
            std::shared_ptr<Property> property = std::dynamic_pointer_cast<Property>(actionField);
            if (property) {
                playerProperties.push_back(property);
            }
        }
    }

    return playerProperties;
}


void Board::drawProperties() {
    std::vector<std::shared_ptr<Property>> properties = getPlayersProperties();
}