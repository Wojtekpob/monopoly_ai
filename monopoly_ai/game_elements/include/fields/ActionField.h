/*
 * This file defines the ActionField class, representing a field in a game that can perform actions involving players.
 * It includes data on the field's ID, name, color, and ownership status.
 * The class is an abstract base class with pure virtual methods `invokeAction` and `nextRound` that must be implemented in derived classes.
 * It also contains methods for checking action availability, comparing objects, and retrieving field information.
 */


#ifndef ACTIONFIELD_H
#define ACTIONFIELD_H

#include <string>
#include <memory>
#include "Player.h"
#include "Action.h"
#include "TextRenderer.h"

class ActionField {
public:
    ActionField(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer) : id_(id), name_(name), color_(color), owned_(false),
        textRenderer_(textRenderer) {}
    virtual ~ActionField() = default;
    virtual void invokeAction(std::shared_ptr<Player> player) = 0;
    virtual void nextRound() = 0;
    bool operator==(const ActionField& other) const {
        return id_ == other.id_ && name_ == other.name_;
    }
    virtual bool isActionAvailable(std::shared_ptr<Player> player, Action action) {
        switch (action) {
        case Action::PLEDGE_PROPERTY:
            return player->getProperties().size() > 0;
        case Action::REDEEM_PLEDGE:
            return player->getProperties().size() > 0;
        default:
            return false;
        }
    }
    virtual Action getMandatoryAction(std::shared_ptr<Player> player) {
        return Action::END;
    }

    virtual std::string getStr(Action action) {
        return name_;
    }
    virtual std::string getDescription() {
        return name_;
    }
    int getId() {
        return id_;
    };
    std::string name_;
    sf::Color color_;
    bool owned_;
    sf::Color owner_color_;
    


protected:
    std::shared_ptr<TextRenderer> textRenderer_;
    int id_;
};

#endif // ACTIONFIELD_H
