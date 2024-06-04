/*
 * This file defines the Property class, a subclass of ActionField.
 * The Property class represents a type of field in a game that can be owned by players.
 * It includes methods for buying, pledging, and redeeming pledges on the property, as well as handling rent payments.
 * The class manages the property's cost, ownership status, and whether it is pledged.
 * It overrides several methods from ActionField to provide specific behaviors for properties.
 * Author: Mikołaj Sendybył
 */

#ifndef PROPERTY_H
#define PROPERTY_H

#include "ActionField.h"

class Property : public ActionField {
public:
    Property(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer, int cost);

    void buy(std::shared_ptr<Player> player);
    void pledge(std::shared_ptr<Player> player);
    void redeemPledge(std::shared_ptr<Player> player);
    int getRedeemPledgePrice();
    int getPledgePrice();
    std::string getStr(Action action) override;
    void nextRound() override;
    std::string getDescription() override;
    Action getMandatoryAction(std::shared_ptr<Player> player) override;
    void virtual clearProperty();

    bool pledged_;
protected:

    std::shared_ptr<Player> owner_;
    int cost_;
    bool rent_paid_;
};

#endif // PROPERTY_H
