/*
 * This file defines the BlankField class, a subclass of ActionField.
 * The BlankField class represents a field in a game where no specific action is taken when a player lands on it.
 * It overrides the `invokeAction` method to provide its specific behavior and leaves `nextRound` as an empty implementation.
 * Author: Mikołaj Sendybył
 */

#ifndef BLANKFIELD_H
#define BLANKFIELD_H

#include "ActionField.h"

class BlankField : public ActionField {
public:
    BlankField(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer);

    void nextRound() override {};


    void invokeAction(std::shared_ptr<Player> player) override;
};

#endif // BLANKFIELD_H
