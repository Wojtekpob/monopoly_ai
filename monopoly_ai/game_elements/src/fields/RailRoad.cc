#include "fields/RailRoad.h"
#include <iostream>
#include <cmath>

RailRoad::RailRoad(int id, const std::string& name, int cost, int rent)
    : Property(id, name, cost), rent_(rent) {}

void RailRoad::invokeAction(std::shared_ptr<Player> player) {
    if (owner_) {
        if (player != owner_) {
            player->decreaseMoney(getRent());
            owner_->increaseMoney(getRent());
        }
    }
    else {
        buy(player);
        player->incrementRailRoads();
    }
}

bool RailRoad::isActionAvailable(std::shared_ptr<Player> player, Action action) {
    switch (action) {
    case Action::BUY_PROPERTY:
        return owner_ == nullptr && player->getMoney() >= cost_;
    case Action::PAY_RENT:
        return owner_ != nullptr && player != owner_ && player->getMoney() >= getRent();
    default:
        return Property::isActionAvailable(player, action);
    }
}

int RailRoad::getRent() {
    return std::pow(2, owner_->getUtilities() - 1) * 25;
}