#include "fields/Property.h"
#include <iostream>

Property::Property(const std::string& name, int cost)
    : ActionField(name), pledged_(false), owner_(nullptr), cost_(cost) {}

void Property::invokeAction(std::shared_ptr<Player> player) {
    // Example action: print property details
    std::cout << "Invoking action on property: " << name_ << " with cost " << cost_ << std::endl;
    // Add more logic based on the game rules
}
