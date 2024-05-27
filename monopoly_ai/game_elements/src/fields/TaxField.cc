#include "fields/TaxField.h"
#include <iostream>

TaxField::TaxField(int id, const std::string& name, int taxAmount)
    : ActionField(id, name), taxAmount_(taxAmount) {}

void TaxField::invokeAction(std::shared_ptr<Player> player) {
    std::cout << "Tax field: " << name_ << " - Pay tax: " << taxAmount_ << std::endl;
    player->decreaseMoney(taxAmount_);
}


bool TaxField::isActionAvailable(std::shared_ptr<Player> player, Action& action) {
    // Logic for TaxField, typically always available
    return true;
}