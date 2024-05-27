#include "fields/Estate.h"
#include <iostream>
Estate::Estate(int id, const std::string& name, int cost, int houseCost, int hotelCost, std::vector<int> houses_rent, std::string province) 
    : Property(id, name, cost), hotels_(0), houses_(0), houseCost_(houseCost), hotelCost_(hotelCost), houses_rent_(houses_rent), province_(province) {}

void Estate::invokeAction(std::shared_ptr<Player> player) {
    // Example action: print estate details
    std::cout << "Estate: " << name_ << " - Houses: " << houses_ << ", Hotels: " << hotels_ << std::endl;
    // Add more logic based on the game rules
}
