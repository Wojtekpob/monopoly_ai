/*
 * This file defines the RailRoad class, a subclass of Property.
 * The RailRoad class represents a type of property in a game that functions as a railroad.
 * It includes methods for handling actions such as buying the railroad, paying rent, and calculating rent based on the number of railroads owned by a player.
 * The class manages the cost and rent of the railroad and overrides several methods from Property to provide specific behaviors for railroads.
 */

#ifndef RAILROAD_H
#define RAILROAD_H

#include "Property.h"

class RailRoad : public Property {
public:
    RailRoad(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer, int cost, int rent);

    void invokeAction(std::shared_ptr<Player> player) override;
    bool isActionAvailable(std::shared_ptr<Player> player, Action action) override;
    int getRent();
    std::string getStr(Action action) override;
    //void nextRound() override {};

private:
    int rent_;
};

#endif // RAILROAD_H
