#include "fields/RailRoad.h"
#include <iostream>

RailRoad::RailRoad(int id, const std::string& name, int cost)
    : Property(id, name, cost) {}

void RailRoad::invokeAction(std::shared_ptr<Player> player) {
    std::cout << "Railroad: " << name_ << " - Action taken." << std::endl;
    // Add more logic based on the game rules
}
