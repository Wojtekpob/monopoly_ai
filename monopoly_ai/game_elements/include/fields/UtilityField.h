/*
 * This file defines the UtilityField class, a subclass of Property.
 * The UtilityField class represents a type of property in a game that functions as a utility.
 * It includes methods for handling actions such as buying the utility, paying rent, and calculating rent based on the number of utilities owned by a player.
 * The class manages the cost and rent of the utility and overrides several methods from Property to provide specific behaviors for utilities.
 */

#ifndef UTILITYFIELD_H
#define UTILITYFIELD_H

#include "Property.h"

class UtilityField : public Property {
public:
    UtilityField(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer, int cost, int rent);

    void invokeAction(std::shared_ptr<Player> player) override;
    bool isActionAvailable(std::shared_ptr<Player> player, Action action) override;
    int getRent();
    std::string getStr(Action action) override;
    //void nextRound() override;

private:
    int rent_;
};

#endif // UTILITYFIELD_H
