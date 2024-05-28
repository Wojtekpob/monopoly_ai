#include "fields/TaxField.h"
#include <iostream>

TaxField::TaxField(int id, const std::string& name, int taxAmount)
    : ActionField(id, name), taxAmount_(taxAmount) {}

void TaxField::invokeAction(std::shared_ptr<Player> player) {
    if (isActionAvailable(player, Action::PAY_TAX))
        player->decreaseMoney(taxAmount_);
}

bool TaxField::isActionAvailable(std::shared_ptr<Player> player, Action action) {
    switch (action) {
    case Action::PAY_TAX:
        return player->getMoney() >= taxAmount_;
    default:
        return false;
    }
}

std::string TaxField::getStr(Action action) {
    std::string str;
    str += ActionField::getStr(action) + "\n";
    return str + "Podatek: " + std::to_string(taxAmount_);
}