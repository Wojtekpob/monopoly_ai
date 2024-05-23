#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Drawable.h"
#include "BoardSquare.h"

class Player : public Drawable {
public:
    Player(std::shared_ptr<sf::RenderWindow> win, std::shared_ptr<BoardSquare> startSquare, sf::Vector2f& position_bias);
    void draw() override;
    void move(int steps, const std::vector<std::shared_ptr<BoardSquare>>& boardSquares);
    std::shared_ptr<BoardSquare> getCurrentSquare() const;
    void setPosition(sf::Vector2f &pos);

private:
    sf::CircleShape circle_;
    std::shared_ptr<BoardSquare> currentSquare_;
    int position_;
    sf::Vector2f position_bias_;
};

#endif // PLAYER_H
