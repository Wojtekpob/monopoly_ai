#include "fields/UtilityField.h"
#include <iostream>

UtilityField::UtilityField(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer, int cost, int rent)
    : Property(id, name, color, textRenderer, cost), rent_(rent) {}

void UtilityField::invokeAction(std::shared_ptr<Player> player) {
    if (owner_) {
        if (player != owner_) {
            player->decreaseMoney(getRent());
            owner_->increaseMoney(getRent());
            rent_paid_ = true;
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
        return owner_ != nullptr && player != owner_ && !pledged_ && !rent_paid_ && player->getMoney() >= getRent();
    default:
        return ActionField::isActionAvailable(player, action);
    }
}

int UtilityField::getRent() {
    return owner_->getUtilities() * 40;
}

std::string UtilityField::getStr(Action action) {
    std::string str;
    str = Property::getStr(action);
    if (owner_) {
        str = str + "\n" + "Czynsz: " + std::to_string(getRent());
    }
    return str;
}