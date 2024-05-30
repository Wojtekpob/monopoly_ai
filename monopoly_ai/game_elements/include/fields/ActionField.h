#ifndef ACTIONFIELD_H
#define ACTIONFIELD_H

#include <string>
#include <memory>
#include "Player.h"
#include "Action.h"

class ActionField {
public:
    ActionField(int id, const std::string& name, sf::Color& color) : id_(id), name_(name), color_(color) {}
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


protected:

    int id_;
};

#endif // ACTIONFIELD_H
