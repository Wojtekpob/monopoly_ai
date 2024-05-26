#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Drawable.h"
#include "BoardSquare.h"

class Player : public Drawable {
public:
    Player(std::shared_ptr<sf::RenderWindow> win, std::shared_ptr<BoardSquare> startSquare, sf::Vector2f& position_bias, int id);
    void draw() override;
    void move(int steps, const std::vector<std::shared_ptr<BoardSquare>>& boardSquares);
    std::shared_ptr<BoardSquare> getCurrentSquare() const;
    void setPosition(sf::Vector2f &pos);
    bool operator==(const Player& other) const;
    int getMoney() const;
    void decreaseMoney(int amount);
    void increaseMoney(int amount);
    void addProperty(int property_id);

private:
    sf::CircleShape circle_;
    std::shared_ptr<BoardSquare> currentSquare_;
    int position_;
    sf::Vector2f position_bias_;
    int id_;
    int money_;
    std::vector<int> properties_;
};

#endif // PLAYER_H
