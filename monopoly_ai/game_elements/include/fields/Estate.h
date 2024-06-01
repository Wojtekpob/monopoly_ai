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
