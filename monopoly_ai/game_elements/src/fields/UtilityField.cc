#include "fields/UtilityField.h"
#include <iostream>

UtilityField::UtilityField(int id, const std::string& name, int cost, int rent)
    : Property(id, name, cost), rent_(rent) {}

void UtilityField::invokeAction(std::shared_ptr<Player> player) {
    std::cout << "Utility field: " << name_ << " - Action taken." << std::endl;
    // Add more logic based on the game rules
}
