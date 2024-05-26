#include "fields/TaxField.h"
#include <iostream>

TaxField::TaxField(const std::string& name, int taxAmount)
    : ActionField(name), taxAmount_(taxAmount) {}

void TaxField::invokeAction(std::shared_ptr<Player> player) {
    std::cout << "Tax field: " << name_ << " - Pay tax: " << taxAmount_ << std::endl;
    player->decreaseMoney(taxAmount_);
}
