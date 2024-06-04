#include <iostream>
#include "fields/GoToJailField.h"

GoToJailField::GoToJailField(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer) : ActionField(id, name, color, textRenderer) {}

void GoToJailField::invokeAction(std::shared_ptr<Player> player) {
    std::cout << "Go to Jail: " << name_ << " - Player sent to jail." << std::endl;
}

bool GoToJailField::isActionAvailable(std::shared_ptr<Player> player, Action action) {
    return false;
}
