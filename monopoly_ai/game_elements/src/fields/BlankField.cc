#include "fields/BlankField.h"
#include <iostream>

BlankField::BlankField(int id, const std::string& name) : ActionField(id, name) {}

void BlankField::invokeAction(std::shared_ptr<Player> player) {
    std::cout << "Blank field: " << name_ << " - No action taken." << std::endl;
}


bool BlankField::isActionAvailable(std::shared_ptr<Player> player, Action& action) {
    // Logic for BlankField, typically always available
    return true;
}