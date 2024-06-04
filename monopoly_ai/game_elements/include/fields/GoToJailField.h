/*
 * This file defines the GoToJailField class, a subclass of ActionField.
 * The GoToJailField class represents a game field that sends a player to jail when they land on it.
 * It overrides the `invokeAction` method to specify the action of sending the player to jail.
 * The `isActionAvailable` method always returns false, indicating no specific actions are available on this field.
 * Author: Mikołaj Sendybył
 */

#ifndef GOTOJAILFIELD_H
#define GOTOJAILFIELD_H

#include "ActionField.h"

class GoToJailField : public ActionField {
public:
    GoToJailField(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer);
    bool isActionAvailable(std::shared_ptr<Player> player, Action action) override;
    void invokeAction(std::shared_ptr<Player> player) override;
    void nextRound() override {};
};

#endif // GOTOJAILFIELD_H
