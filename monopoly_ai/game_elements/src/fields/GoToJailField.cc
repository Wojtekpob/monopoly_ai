#include "fields/GoToJailField.h"
#include <iostream>

GoToJailField::GoToJailField(const std::string& name) : ActionField(name) {}

void GoToJailField::invokeAction(std::shared_ptr<Player> player) {
    std::cout << "Go to Jail: " << name_ << " - Player sent to jail." << std::endl;
    // Add logic to move player to the jail position
}
