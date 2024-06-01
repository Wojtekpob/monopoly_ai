#include "TextRenderer.h"
#include "fields/Estate.h"

TextRenderer::TextRenderer(std::shared_ptr<sf::RenderWindow> win)
    : window_(win) {
    initializeTexts();
}

void TextRenderer::initializeTexts() {
    if (!font_.loadFromFile(std::string(BASE_PATH) + "assets/fonts/font.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    text_.setFont(font_);

    player_text_.setFont(font_);
    player_text_.setCharacterSize(24);

    action_text_.setFont(font_);
    action_text_.setCharacterSize(24);
    action_text_.setPosition(610.0f, 5.0f);

    fields_text_.setFont(font_);
    fields_text_.setCharacterSize(18);
    fields_text_.setPosition(800.0f, 5.0f);

    communicats_text_.setFont(font_);
    communicats_text_.setCharacterSize(24);
    communicats_text_.setPosition(5.0f, 700.0f);

    keys_text_.setFont(font_);
    keys_text_.setCharacterSize(30);
    keys_text_.setPosition(5.0f, 550.0f);
}

void TextRenderer::renderText(const std::string& text, const sf::Vector2f& position, const sf::Color& color, unsigned int size) {
    text_.setString(text);
    text_.setPosition(position);
    text_.setFillColor(color);
    text_.setCharacterSize(size);
    //window_.draw(text_);
}

void TextRenderer::renderPlayers(std::vector<std::shared_ptr<Player>>& players, int current_player) {
    player_text_.setOutlineColor(sf::Color::White);
    player_text_.setOutlineThickness(0.5f);

    for (int i = 0; i < players.size(); ++i) {

        std::string money = std::to_string(players[i]->getMoney());
        player_text_.setString("Player " + std::to_string(i) + "\t\t\t" + money + " $");
        player_text_.setColor(players[i]->getColor());

        if (i == current_player) {
            player_text_.setOutlineColor(sf::Color::Green);
            player_text_.setOutlineThickness(2.0f);
        }
        else {
            player_text_.setOutlineColor(sf::Color::White);
            player_text_.setOutlineThickness(0.5f);
        }
        window_->draw(player_text_);
        player_text_.move(0.0f, 24.0f);
    }
    player_text_.setPosition(0.0f, 0.0f);
}


void TextRenderer::renderSquaresDescription(std::vector<std::shared_ptr<BoardSquare>>& squares, int selected_property) {
    std::string str;
    for (auto square : squares) {
        fields_text_.setPosition(fields_text_.getPosition() + sf::Vector2f(0.0, 20.0));
        fields_text_.setString(square->actionField_->getDescription());
        fields_text_.setFillColor(square->actionField_->color_);

        if (selected_property == square->actionField_->getId()) {
            sf::RectangleShape highlightRect;
            highlightRect.setSize(sf::Vector2f(fields_text_.getLocalBounds().width, fields_text_.getLocalBounds().height + 5.0));
            highlightRect.setFillColor(sf::Color::Yellow);
            highlightRect.setPosition(fields_text_.getPosition());
            window_->draw(highlightRect);
        }

        if (square->actionField_->owned_) {
            sf::RectangleShape ownerRect;
            ownerRect.setSize(sf::Vector2f(20.0f, 20.0f));
            ownerRect.setFillColor(square->actionField_->owner_color_);
            ownerRect.setPosition(fields_text_.getPosition().x - 25.0f, fields_text_.getPosition().y);
            window_->draw(ownerRect);
            auto estate = std::dynamic_pointer_cast<Estate>(square->actionField_);
            if (estate) {
                if (estate->getHotels() == 1) {
                    sf::CircleShape hotelCircle(10.0f);
                    hotelCircle.setFillColor(sf::Color::Red);
                    hotelCircle.setPosition(fields_text_.getPosition().x + fields_text_.getLocalBounds().width + 10.0f, fields_text_.getPosition().y);
                    window_->draw(hotelCircle);
                }
                else {
                    for (int i = 0; i < estate->getHouses(); ++i) {
                        sf::CircleShape houseCircle(5.0f);
                        houseCircle.setFillColor(sf::Color::Green);
                        houseCircle.setPosition(fields_text_.getPosition().x + fields_text_.getLocalBounds().width + 12.0f + i * 15.0f, fields_text_.getPosition().y);
                        window_->draw(houseCircle);
                    }
                }
            }
        }

        window_->draw(fields_text_);
    }
    fields_text_.setPosition(950.0f, 5.0f);
}