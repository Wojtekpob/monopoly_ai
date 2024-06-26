/*
 * This file defines the Board class, which manages the game board, players, and their interactions.
 * The Board class is responsible for initializing the game elements, handling player actions, running game rounds,
 * and rendering the board and its components. It includes methods for player movement, dice rolling, action execution,
 * property management, and various rendering tasks. The class maintains the state of the game and ensures the correct
 * sequence of gameplay events.
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "BoardSquare.h"
#include "Drawable.h"
#include "Player.h"
#include "Dice.h"
#include "Action.h"
#include "fields/Property.h"
#include "fields/FieldLoader.h"
#include "Color.h"
#include "TextRenderer.h"

class Board : public Drawable {
public:
    Board(float width, float height, std::shared_ptr<sf::RenderWindow> win);
    void draw() override;
    void setPosition(float x, float y);
    void runRound();
    void performCurrentAction();
    void nextPlayer();
    void drawAction();
    void incrementAction();
    void decrementAction();
    void setActionAvailability();
    void drawLeaderBoard();
    std::vector<std::shared_ptr<Property>> getPlayersProperties(int state);
    std::shared_ptr<Player> getCurrentPlayer();
    void drawSquaresDescription();
    void nextProperty();
    void previousProperty();
    std::shared_ptr<Property> getCurrentlySelectedProperty();
    void startPropertySelection();
    void closePropertySelection();
    void actionOnProperty();
    void drawKeysText();
    void playerSurrender();
    void finishGame();


    bool dice_tossed_;
    int selected_property_;
    bool property_selection_;
    bool game_end_;

private:
    void initializeSquares(float pos_x, float pos_y);
    void initializePlayers(int players);
    bool isActionAvailable(Action& action);
    void initializeTexts();
    void incrementPlayer();


    std::shared_ptr<TextRenderer> textRenderer;
    sf::RectangleShape shape_;
    std::vector<std::shared_ptr<BoardSquare>> squares_;
    sf::Texture texture_;
    std::vector<std::shared_ptr<Player>> players_;
    std::unique_ptr<Dice> dice_;
    Action current_action_;
    sf::Font font_;
    sf::Text communicatsText_;
    bool action_available_;
    std::unique_ptr<FieldLoader> fieldLoader_;
    std::shared_ptr<int> current_player_;
};

#endif // BOARD_H
