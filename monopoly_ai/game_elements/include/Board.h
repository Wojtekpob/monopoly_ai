#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "BoardSquare.h"
#include "Drawable.h"
#include "Player.h"
#include "Dice.h"
#include "Action.h"
#include "fields/Property.h"
#include "fields/FieldLoader.h"
#include "Color.h"

class Board : public Drawable {
public:
    Board(float width, float height, std::shared_ptr<sf::RenderWindow> win);
    void draw() override;
    void setPosition(float x, float y); // Deklaracja funkcji
    void runRound();
    void performCurrentAction();
    void nextPlayer();
    void drawAction();
    void incrementAction();
    void decrementAction();
    void setActionAvailability();
    void drawLeaderBoard();
    std::vector<std::shared_ptr<Property>> getPlayersProperties();
    void drawProperties();
    std::shared_ptr<Player> getCurrentPlayer();
    void drawSquaresDescription();
    void nextProperty();
    void previousProperty();


    bool dice_tossed_;
    int selected_property_;

private:
    void initializeSquares(float pos_x, float pos_y);
    void initializePlayers(int players);
    bool isActionAvailable(Action& action);
    void updatePlayerText();


    int current_player_;
    sf::RectangleShape shape_;
    std::vector<std::shared_ptr<BoardSquare>> squares_;
    sf::Texture texture_;
    std::vector<std::shared_ptr<Player>> players_;
    std::unique_ptr<Dice> dice_;
    Action current_action_;
    sf::Font font_;
    sf::Text actionText_;
    sf::Text playerText_;
    sf::Text fieldsText_;
    bool action_available_;
    FieldLoader fieldLoader_;

};

#endif // BOARD_H
