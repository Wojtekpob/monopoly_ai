#include "fields/TaxField.h"
#include <iostream>

TaxField::TaxField(int id, const std::string& name, int taxAmount)
    : ActionField(id, name), taxAmount_(taxAmount), paid_(false) {}

void TaxField::invokeAction(std::shared_ptr<Player> player) {
    if (isActionAvailable(player, Action::PAY_TAX)) {
        player->decreaseMoney(taxAmount_);
        paid_ = true;
    }
}

bool TaxField::isActionAvailable(std::shared_ptr<Player> player, Action action) {
    switch (action) {
    case Action::PAY_TAX:
        return !paid_ && player->getMoney() >= taxAmount_;
    default:
        return false;
    }
}

std::string TaxField::getStr(Action action) {
    std::string str;
    str += ActionField::getStr(action) + "\n";
    return str + "Podatek: " + std::to_string(taxAmount_);
}

void TaxField::nextRound() {
    paid_ = true;
}