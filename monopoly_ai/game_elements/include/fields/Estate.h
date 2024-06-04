/*
 * This file defines the Estate class, a subclass of Property.
 * The Estate class represents a type of property in a game that can have houses and hotels built on it.
 * It includes methods to handle actions such as buying houses, buying hotels, and paying rent.
 * The class also manages information about the property's province, number of houses, number of hotels,
 * and the associated costs and rents.
 */

#ifndef ESTATE_H
#define ESTATE_H

#include "Property.h"

class Estate : public Property {
public:
    Estate(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer,  int cost, int houseCost, int hotelCost, std::vector<int> houses_rent, std::string province);

    void invokeAction(std::shared_ptr<Player> player) override;
    bool isActionAvailable(std::shared_ptr<Player> player, Action action) override;
    std::string getStr(Action action) override;
    void nextRound() override;
    void clearProperty() override;

    std::string province_;
    int getHotels();
    int getHouses();

private:
    void buyHouse(std::shared_ptr<Player> player);
    void buyHotel(std::shared_ptr<Player> player);
    void payRent(std::shared_ptr<Player> player);

    int hotels_;
    int houses_;
    int houseCost_;
    int hotelCost_;
    std::vector<int> houses_rent_;
    bool bought_;
};

#endif // ESTATE_H
