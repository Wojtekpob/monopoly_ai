#include "Property.h"
#include <iostream>

Property::Property(const std::string& name, int cost)
    : pledged_(false), owner_(nullptr), cost_(cost) {
    name_ = name;
}

void Property::invokeAction(std::shared_ptr<Player> player) {
    std::cout << "Invoking action on property: " << name_ << " with cost " << cost_ << std::endl;

}
