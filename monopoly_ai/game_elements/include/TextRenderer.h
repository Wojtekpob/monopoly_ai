#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"
#include "Action.h"

class TextRenderer {
public:
    TextRenderer(std::shared_ptr<sf::RenderWindow> win);

    void renderText(const std::string& text, const sf::Vector2f& position, const sf::Color& color, unsigned int size = 24);
    void renderPlayers(std::vector<std::shared_ptr<Player>>& players, int current_player);
    void renderSquaresDescription(std::vector<std::shared_ptr<BoardSquare>>& squares, int selected_property);
    void renderAction(Action action, bool action_available, std::shared_ptr<ActionField> action_field);

private:
    void initializeTexts();

    sf::Font font_;
    sf::Text text_;
    sf::Text action_text_;
    sf::Text player_text_;
    sf::Text fields_text_;
    sf::Text communicats_text_;
    sf::Text keys_text_;
    std::shared_ptr<sf::RenderWindow> window_;
};