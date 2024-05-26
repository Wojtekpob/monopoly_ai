#include "fields/BlankField.h"
#include <iostream>

BlankField::BlankField(const std::string& name) : ActionField(name) {}

void BlankField::invokeAction(std::shared_ptr<Player> player) {
    std::cout << "Blank field: " << name_ << " - No action taken." << std::endl;
}
