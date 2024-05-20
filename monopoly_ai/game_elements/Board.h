#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "BoardSquare.h"
#include "Drawable.h"

class Board : public Drawable {
public:
    Board(float width, float height, std::shared_ptr<sf::RenderWindow> win);
    void draw() override;
    void setPosition(float x, float y); // Deklaracja funkcji

private:
    void initializeSquares(float pos_x, float pos_y);

    sf::RectangleShape shape_;
    std::vector<BoardSquare> squares_;
};

#endif // BOARD_H
