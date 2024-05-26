#ifndef ACTIONFIELD_H
#define ACTIONFIELD_H

#include <string>
#include <memory>
#include "Player.h"

class ActionField {
public:
    ActionField(int id, const std::string& name) : id_(id), name_(name) {}
    virtual ~ActionField() = default;
    virtual void invokeAction(std::shared_ptr<Player> player) = 0;
    bool operator==(const ActionField& other) const {
        return id_ == other.id_ && name_ == other.name_;
    }

protected:
    std::string name_;
    int id_;
};

#endif // ACTIONFIELD_H
