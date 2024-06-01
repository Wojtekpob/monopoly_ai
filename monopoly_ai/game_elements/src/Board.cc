#include <iostream>
#include "Board.h"

Board::Board(float width, float height, std::shared_ptr<sf::RenderWindow> win)
    : Drawable(win), current_action_(Action::BUY_PROPERTY), dice_tossed_(false),
    selected_property_(-1), property_selection_(false) {
    current_player_ = std::make_shared<int>(0);
    textRenderer = std::make_shared<TextRenderer>(window_);
    fieldLoader_ = std::make_unique<FieldLoader>(textRenderer);
    dice_ = std::make_unique<Dice>(win);
    shape_.setSize(sf::Vector2f(width, height));
    shape_.setFillColor(sf::Color::White);
    initializeSquares(200.0f, 100.0f);
    initializePlayers(4);
    setActionAvailability();
    initializeTexts();
}

int getIndexById(std::vector<std::shared_ptr<Player>>& players, int id) {
    int i = 0;
    for (auto player : players) {
        if (id == player->id_) return i;
        i++;
    }
}

void Board::initializeTexts() {
    if (!font_.loadFromFile(std::string(BASE_PATH) + "assets/fonts/font.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    communicatsText_.setFont(font_);
    communicatsText_.setCharacterSize(24);
    communicatsText_.setPosition(5.0f, 700.0f);

}

void Board::drawKeysText() {
    textRenderer->renderHotKeys(property_selection_, dice_tossed_);
}

void Board::runRound() {
    dice_->throwDice();
    textRenderer->addCommunicat(getCurrentPlayer()->to_string() + " wyrzucil " + std::to_string(dice_->getValue()));
    getCurrentPlayer()->move(dice_->getValue(), squares_);
    dice_tossed_ = true;
    setActionAvailability();
}

std::shared_ptr<Player> Board::getCurrentPlayer() {
    for (auto player : players_) {
        if (player->id_ == *current_player_) return player;
    }
    return nullptr;
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
    if (!action_available_) {
        textRenderer->addCommunicat("Akcja niedozwolona");
        return;
    }

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
    return currentSquare->actionField_->isActionAvailable(player, action);
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
        window_->draw(communicatsText_);
        drawKeysText();
        textRenderer->renderCommunicats();
    }
}

void Board::initializePlayers(int players=2) {
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
    std::vector<std::shared_ptr<ActionField>> fields = fieldLoader_->loadFields(std::string(BASE_PATH) + "assets/fields/fields.json");
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
    }
   
}

void Board::setPosition(float x, float y) {
    shape_.setPosition(sf::Vector2f(x, y));
}

void Board::incrementPlayer() {
    ++(*current_player_);

    if (*current_player_ > players_.back()->id_) {
        *current_player_ = players_.front()->id_;
    }

    while (!getCurrentPlayer() || *current_player_ != getCurrentPlayer()->id_) {
        ++(*current_player_);

        if (*current_player_ > players_.back()->id_) {
            *current_player_ = players_.front()->id_;
        }
    }
}

void Board::nextPlayer() {
    Action mandatoryAction = getCurrentPlayer()->getCurrentSquare()->actionField_->getMandatoryAction(getCurrentPlayer());
    if (mandatoryAction != Action::END) {}
    else {

        getCurrentPlayer()->getCurrentSquare()->actionField_->nextRound();
        /**current_player_ = (*current_player_ + 1) % players_.size();*/
        incrementPlayer();
        current_action_ = Action::BUY_PROPERTY;
        setActionAvailability();
        dice_tossed_ = false;
        selected_property_ = -1;
    }
}

void Board::drawSquaresDescription() {
    textRenderer->renderSquaresDescription(squares_, selected_property_);
}

void Board::drawAction() {
    textRenderer->renderAction(current_action_, action_available_, getCurrentPlayer()->getCurrentSquare()->actionField_);
}

void Board::incrementAction() {
    ++current_action_;
    setActionAvailability();
}

void Board::decrementAction() {
    --current_action_;
    setActionAvailability();
}

void Board::drawLeaderBoard() {
    textRenderer->renderPlayers(players_, getIndexById(players_, *current_player_));
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


void Board::playerSurrender() {
    auto playersProperties = getPlayersProperties(0);
    getCurrentPlayer()->getCurrentSquare()->actionField_->nextRound();
    for (std::shared_ptr<Property> property : playersProperties) {
        property->clearProperty();
    }

    players_.erase(players_.begin() + getIndexById(players_, *current_player_));
    
    if (players_.size() == 1) finishGame();
    else {
        incrementPlayer();
        current_action_ = Action::BUY_PROPERTY;
        setActionAvailability();
        dice_tossed_ = false;
        selected_property_ = -1;
    }
}


void Board::finishGame() {}