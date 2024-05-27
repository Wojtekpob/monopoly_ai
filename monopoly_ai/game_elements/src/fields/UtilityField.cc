#include "fields/UtilityField.h"
#include <iostream>

UtilityField::UtilityField(int id, const std::string& name, int cost, int rent)
    : Property(id, name, cost), rent_(rent) {}

void UtilityField::invokeAction(std::shared_ptr<Player> player) {
    std::cout << "Utility field: " << name_ << " - Action taken." << std::endl;
    // Add more logic based on the game rules
}


bool UtilityField::isActionAvailable(std::shared_ptr<Player> player, Action action) {
    // Implement the logic to check if the action is available for the player
    // Example: Check if the player can pay the rent
    return true; // Placeholder logic
}