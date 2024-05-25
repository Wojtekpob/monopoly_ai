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

class Board : public Drawable {
public:
    Board(float width, float height, std::shared_ptr<sf::RenderWindow> win);
    void draw() override;
    void setPosition(float x, float y); // Deklaracja funkcji
    void runRound();
    void performCurrentAction();

private:
    void initializeSquares(float pos_x, float pos_y);
    void initializePlayers(int players);
    bool isActionAvailable(Action& action);


    int current_player_;
    sf::RectangleShape shape_;
    std::vector<std::shared_ptr<BoardSquare>> squares_;
    sf::Texture texture_;
    std::vector<std::shared_ptr<Player>> players_;
    std::unique_ptr<Dice> dice_;
    Action current_action_;
};

#endif // BOARD_H
