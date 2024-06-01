#include <iostream>
#include "Board.h"

Board::Board(float width, float height, std::shared_ptr<sf::RenderWindow> win)
    : Drawable(win), current_action_(Action::BUY_PROPERTY), fieldLoader_(), dice_tossed_(false),
    selected_property_(-1), property_selection_(false) {
    current_player_ = std::make_shared<int>(0);
    dice_ = std::make_unique<Dice>(win);
    shape_.setSize(sf::Vector2f(width, height));
    shape_.setFillColor(sf::Color::White);
    initializeSquares(200.0f, 100.0f);
    initializePlayers(4);
    setActionAvailability();


    initializeTexts();

}

void Board::initializeTexts() {
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

    communicatsText_.setFont(font_);
    communicatsText_.setCharacterSize(24);
    communicatsText_.setPosition(5.0f, 550.0f);

    keysText_.setFont(font_);
    keysText_.setCharacterSize(24);
    keysText_.setPosition(5.0f, 550.0f);

}

void Board::drawKeysText() {
    std::vector<std::string> actions;

    if (!property_selection_) {
        if (!dice_tossed_) {
            actions.push_back("ENTER -> rzuc koscia");
        }
        else {
            actions.push_back("ENTER -> nastepny gracz");
            actions.push_back("I -> wykonaj akcje");
        }
        actions.push_back("RIGHT -> nastepna akcja");
        actions.push_back("LEFT -> poprzednia akcja");
    }
    else {
        if (dice_tossed_) {
            actions.push_back("UP -> poprzednia nieruchomosc");
            actions.push_back("DOWN -> nastepna nieruchomosc");
            actions.push_back("R -> akcja na nieruchomosci");
            actions.push_back("B -> zamknij wybor nieruchomosci");
        }
    }

    float yOffset = 10.0f;
    keysText_.setPosition(yOffset, 550.0f);

    for (const auto& action : actions) {
        keysText_.setString(action);
        window_->draw(keysText_);
        keysText_.move(0.0f, 28.0f);
    }
    keysText_.setPosition(10.0f, 550.0f);
}

void Board::runRound() {
    dice_->throwDice();
    getCurrentPlayer()->move(dice_->getValue(), squares_);
    dice_tossed_ = true;
    setActionAvailability();
}

std::shared_ptr<Player> Board::getCurrentPlayer() {
    return players_[*current_player_];
}

void Board::startPropertySelection() {
    property_selection_ = true;
    selected_property_ = -1;
    nextProperty();
}

void Board::closePropertySelection() {
    property_selection_ = false;
    selected_property_ = -1;
    setActionAvailability();
}

void Board::actionOnProperty() {
    if (current_action_ == Action::PLEDGE_PROPERTY) {
        getCurrentlySelectedProperty()->pledge(getCurrentPlayer());
        nextProperty();
    }
    else if (current_action_ == Action::REDEEM_PLEDGE) {
        getCurrentlySelectedProperty()->redeemPledge(getCurrentPlayer());
        nextProperty();
    }
    if (!isActionAvailable(current_action_)) closePropertySelection();
}

void Board::performCurrentAction() {
    if (!action_available_) return;

    if (current_action_ == Action::PLEDGE_PROPERTY || current_action_ == Action::REDEEM_PLEDGE) {
        startPropertySelection();
        return;
    }

    auto player = getCurrentPlayer();
    auto currentSquare = player->getCurrentSquare();
    currentSquare->actionField_->invokeAction(player);
    setActionAvailability();
}

void Board::setActionAvailability() {
    action_available_ = isActionAvailable(current_action_);
}

bool Board::isActionAvailable(Action& action) {
    auto player = getCurrentPlayer();
    auto currentSquare = player->getCurrentSquare();
    switch (current_action_) {
    case Action::PLEDGE_PROPERTY:
        if (getPlayersProperties(1).empty()) return false;
        break;
    case Action::REDEEM_PLEDGE:
        if (getPlayersProperties(2).empty()) return false;
        break;
    }
    auto a = currentSquare->actionField_->isActionAvailable(player, action);
    return a;
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
        drawSquaresDescription();
        //window_->draw(communicatsText_);
        drawKeysText();
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
        players_.push_back(std::make_shared<Player>(window_, squares_[0], position_biases[i], i, current_player_));
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
                continue;
            }

            std::string textContent = "Property";
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
    Action mandatoryAction = getCurrentPlayer()->getCurrentSquare()->actionField_->getMandatoryAction(getCurrentPlayer());
    if (mandatoryAction != Action::END) {}
    else {
        getCurrentPlayer()->getCurrentSquare()->actionField_->nextRound();
        *current_player_ = (*current_player_ + 1) % players_.size();
        current_action_ = Action::BUY_PROPERTY;
        setActionAvailability();
        dice_tossed_ = false;
        selected_property_ = -1;
    }
}

void Board::drawSquaresDescription() {
    std::string str;
    for (auto square : squares_) {
        fieldsText_.setPosition(fieldsText_.getPosition() + sf::Vector2f(0.0, 20.0));
        fieldsText_.setString(square->actionField_->getDescription());
        fieldsText_.setFillColor(square->actionField_->color_);

        if (selected_property_ == square->actionField_->getId()) {
            sf::RectangleShape highlightRect;
            highlightRect.setSize(sf::Vector2f(fieldsText_.getLocalBounds().width, fieldsText_.getLocalBounds().height + 5.0));
            highlightRect.setFillColor(sf::Color::Yellow);
            highlightRect.setPosition(fieldsText_.getPosition());
            window_->draw(highlightRect);
        }

        if (square->actionField_->owned_) {
            sf::RectangleShape ownerRect;
            ownerRect.setSize(sf::Vector2f(20.0f, 20.0f)); 
            ownerRect.setFillColor(square->actionField_->owner_color_);
            ownerRect.setPosition(fieldsText_.getPosition().x - 25.0f, fieldsText_.getPosition().y);
            window_->draw(ownerRect);
            auto estate = std::dynamic_pointer_cast<Estate>(square->actionField_);
            if (estate) {
                if (estate->getHotels() == 1) {
                    sf::CircleShape hotelCircle(10.0f); 
                    hotelCircle.setFillColor(sf::Color::Red);
                    hotelCircle.setPosition(fieldsText_.getPosition().x + fieldsText_.getLocalBounds().width + 10.0f, fieldsText_.getPosition().y);
                    window_->draw(hotelCircle);
                }
                else {
                    for (int i = 0; i < estate->getHouses(); ++i) {
                        sf::CircleShape houseCircle(5.0f); 
                        houseCircle.setFillColor(sf::Color::Green);
                        houseCircle.setPosition(fieldsText_.getPosition().x + fieldsText_.getLocalBounds().width + 12.0f + i * 15.0f, fieldsText_.getPosition().y);
                        window_->draw(houseCircle);
                    }
                }
            }
        }

        window_->draw(fieldsText_);
    }
    fieldsText_.setPosition(950.0f, 5.0f); // Resetowanie pozycji tekstu na koñcu
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
        str = "AKCJA: KUP";
        break;
    case Action::PAY_RENT:
        str = "AKCJA: ZAPLAC CZYNSZ";
        break;
    case Action::BUY_HOUSE:
        str = "AKCJA: KUP DOM";
        break;
    case Action::BUY_HOTEL:
        str = "AKCJA: KUP HOTEL";
        break;
    case Action::PLEDGE_PROPERTY:
        str = "AKCJA: ZASTAW";
        break;
    case Action::PAY_TAX:
        str = "AKCJA ZAPLAC PODATEK";
        break;
    case Action::REDEEM_PLEDGE:
        str = "AKCJA: WYKUP ZASTAW";
        break;
    default:
        str = "Unknown Action";
        break;
    }
    actionText_.setString(str);
    window_->draw(actionText_);
    actionText_.move(0.0f, 25.0f);
    actionText_.setString(getCurrentPlayer()->getCurrentSquare()->actionField_->getStr(Action::REDEEM_PLEDGE));
    actionText_.setColor(sf::Color::Black);
    window_->draw(actionText_);
    actionText_.move(0.0f, -25.0f);
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
    playerText_.setString("Player " + std::to_string(*current_player_) + "\t\t\t" + money + " $");
}

void Board::drawLeaderBoard() {
    playerText_.setOutlineColor(sf::Color::White);
    playerText_.setOutlineThickness(0.5f);

    for (int i = 0; i < players_.size(); ++i) {
        
        std::string money = std::to_string(players_[i]->getMoney());
        playerText_.setString("Player " + std::to_string(i) + "\t\t\t" + money + " $");
        playerText_.setColor(players_[i]->getColor());

        if (i == *current_player_) {
            playerText_.setOutlineColor(sf::Color::Green);
            playerText_.setOutlineThickness(2.0f);
        }
        else {
            playerText_.setOutlineColor(sf::Color::White);
            playerText_.setOutlineThickness(0.5f);
        }
        window_->draw(playerText_);
        playerText_.move(0.0f, 24.0f);
    }
    playerText_.setPosition(0.0f, 0.0f);
}

std::vector<std::shared_ptr<Property>> Board::getPlayersProperties(int state) { // 0 - all // 1 - can be pledged 2 - already pledged
    auto player = getCurrentPlayer();
    std::vector<std::shared_ptr<Property>> playerProperties;

    for (int propertyId : player->getProperties()) {
        if (propertyId >= 0 && propertyId < squares_.size()) {
            std::shared_ptr<ActionField> actionField = squares_[propertyId]->actionField_;
            std::shared_ptr<Property> property = std::dynamic_pointer_cast<Property>(actionField);
            if (property) {
                if (state == 0) {
                    playerProperties.push_back(property);
                }
                else if (state == 1 && !property->pledged_) {
                    playerProperties.push_back(property);
                }
                else if (state == 2 && property->pledged_) {
                    playerProperties.push_back(property);
                }
            }
        }
    }

    return playerProperties;
}

std::shared_ptr<Property> Board::getCurrentlySelectedProperty() {
    if (selected_property_ == -1) throw std::runtime_error("No selected property");
    return std::dynamic_pointer_cast<Property>(squares_[selected_property_]->actionField_);
}

void Board::drawProperties() {
    //std::vector<std::shared_ptr<Property>> properties = getPlayersProperties();
}

void Board::nextProperty() {
    auto player = getCurrentPlayer();
    std::vector<std::shared_ptr<Property>> properties;
    if (current_action_ == Action::PLEDGE_PROPERTY) {
        properties = getPlayersProperties(1);
    }
    else properties = getPlayersProperties(2);

    if (properties.empty()) {
        selected_property_ = -1;
        return;
    }

    if (selected_property_ == -1) {
        selected_property_ = properties[0]->getId();
        return;
    }

    auto it = std::find_if(properties.begin(), properties.end(), [this](const std::shared_ptr<Property>& property) {
        return property->getId() == selected_property_;
        });

    if (it != properties.end()) {
        ++it;
        if (it == properties.end()) {
            selected_property_ = properties[0]->getId();
        }
        else {
            selected_property_ = (*it)->getId();
        }
    }
    else {
        selected_property_ = properties[0]->getId();
    }
}

void Board::previousProperty() {
    auto player = getCurrentPlayer();
    std::vector<std::shared_ptr<Property>> properties;
    if (current_action_ == Action::PLEDGE_PROPERTY) {
        properties = getPlayersProperties(1);
    } else properties = getPlayersProperties(2);
    
    if (properties.empty()) {
        selected_property_ = -1;
        return;
    }

    if (selected_property_ == -1) {
        selected_property_ = properties[0]->getId();
        return;
    }

    auto it = std::find_if(properties.begin(), properties.end(), [this](const std::shared_ptr<Property>& property) {
        return property->getId() == selected_property_;
        });

    if (it != properties.end()) {
        if (it == properties.begin()) {
            selected_property_ = properties.back()->getId();
        }
        else {
            --it;
            selected_property_ = (*it)->getId();
        }
    }
    else {
        selected_property_ = properties[0]->getId();
    }
}
