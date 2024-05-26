#ifndef ESTATE_H
#define ESTATE_H

#include "Property.h"

class Estate : public Property {
public:
    Estate(int id, const std::string& name, int cost, int houseCost, int hotelCost, std::vector<int> houses_rent_);

    void invokeAction(std::shared_ptr<Player> player) override;

private:
    int hotels_;
    int houses_;
    int houseCost_;
    int hotelCost_;
    std::vector<int> houses_rent_;
};

#endif // ESTATE_H
