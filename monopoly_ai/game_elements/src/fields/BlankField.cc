#include <iostream>
#include "fields/BlankField.h"

BlankField::BlankField(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer) : ActionField(id, name, color, textRenderer) {}

void BlankField::invokeAction(std::shared_ptr<Player> player) {
    std::cout << "Blank field: " << name_ << " - No action taken." << std::endl;
}