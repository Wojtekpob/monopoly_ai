/*
 * This file defines the Player class, representing a player in the game.
 * The Player class manages the player's position on the board, money, properties, railroads, and utilities.
 * It includes methods for moving the player, drawing the player on the game window, handling financial transactions,
 * and managing properties. The class also provides functionalities to increment the count of railroads and utilities owned by the player.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <chrono>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "BoardSquare.h"

class Player : public Drawable {
public:
    Player(std::shared_ptr<sf::RenderWindow> win, std::shared_ptr<BoardSquare> startSquare, sf::Vector2f& position_bias, int id, 
        std::shared_ptr<int> current_player);
    void draw() override;
    void move(int steps, const std::vector<std::shared_ptr<BoardSquare>>& boardSquares);
    std::shared_ptr<BoardSquare> getCurrentSquare() const;
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    bool operator==(const Player& other) const;
    int getMoney() const;
    void decreaseMoney(int amount);
    void increaseMoney(int amount);
    void addProperty(int property_id);
    std::vector<int> getProperties();
    int getRailRoads();
    void incrementRailRoads();
    int getUtilities();
    void incrementUtilities();
    std::string to_string() const;
    sf::Color getColor();
    void setColor(sf::Color& color);
    int id_;

private:
    static std::vector<sf::Color> colors_;
    sf::Color color_;
    sf::CircleShape circle_;
    std::shared_ptr<BoardSquare> currentSquare_;
    int position_;
    sf::Vector2f position_bias_;
    int money_;
    std::vector<int> properties_;
    int railroads_;
    int utilities_;
    std::shared_ptr<int> current_player_;
    std::chrono::steady_clock::time_point start_time_;
};

#endif // PLAYER_H
