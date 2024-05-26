#include "fields/Estate.h"
#include <iostream>

Estate::Estate(const std::string& name, int cost, int houseCost, int hotelCost)
    : Property(name, cost), hotels_(0), houses_(0), houseCost_(houseCost), hotelCost_(hotelCost) {}

void Estate::invokeAction(std::shared_ptr<Player> player) {
    // Example action: print estate details
    std::cout << "Estate: " << name_ << " - Houses: " << houses_ << ", Hotels: " << hotels_ << std::endl;
    // Add more logic based on the game rules
}
