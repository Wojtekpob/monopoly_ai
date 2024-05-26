#include "fields/UtilityField.h"
#include <iostream>

UtilityField::UtilityField(const std::string& name, int cost)
    : Property(name, cost) {}

void UtilityField::invokeAction(std::shared_ptr<Player> player) {
    std::cout << "Utility field: " << name_ << " - Action taken." << std::endl;
    // Add more logic based on the game rules
}
