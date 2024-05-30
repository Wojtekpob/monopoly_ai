#include "fields/BlankField.h"
#include <iostream>

BlankField::BlankField(int id, const std::string& name, sf::Color& color) : ActionField(id, name, color) {}

void BlankField::invokeAction(std::shared_ptr<Player> player) {
    std::cout << "Blank field: " << name_ << " - No action taken." << std::endl;
}