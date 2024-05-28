#include "fields/UtilityField.h"
#include <iostream>

UtilityField::UtilityField(int id, const std::string& name, int cost, int rent)
    : Property(id, name, cost), rent_(rent) {}

void UtilityField::invokeAction(std::shared_ptr<Player> player) {
    if (owner_) {
        if (player != owner_) {
            player->decreaseMoney(getRent());
            owner_->increaseMoney(getRent());
        }
    }
    else {
        buy(player);
        player->incrementUtilities();
    }
}

bool UtilityField::isActionAvailable(std::shared_ptr<Player> player, Action action) {
    switch (action) {
    case Action::BUY_PROPERTY:
        return owner_ == nullptr && player->getMoney() >= cost_;
    case Action::PAY_RENT:
        return owner_ != nullptr && player != owner_ && player->getMoney() >= getRent();
    default:
        return Property::isActionAvailable(player, action);
    }
}

int UtilityField::getRent() {
    return owner_->getUtilities() * 40;
}