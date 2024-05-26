#ifndef ACTIONFIELD_H
#define ACTIONFIELD_H

#include <string>
#include <memory>
#include "Player.h"

class ActionField {
public:
    virtual ~ActionField() = default;
    virtual void invokeAction(std::shared_ptr<Player> player) = 0;

protected:
    std::string name_;
};

#endif // ACTIONFIELD_H
