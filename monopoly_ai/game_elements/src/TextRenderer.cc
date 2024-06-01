#include "TextRenderer.h"

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

void TextRenderer::renderPlayers(std::vector<std::shared_ptr<Player>> players, int current_player) {
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