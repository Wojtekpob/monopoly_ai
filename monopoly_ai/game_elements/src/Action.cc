#include "Action.h"

Action& operator++(Action& action) {
    if (action == Action::END) {
        action = Action::BUY_PROPERTY; 
    }
    else {
        action = static_cast<Action>(static_cast<int>(action) + 1);
        if (action == Action::END) {
            action = Action::BUY_PROPERTY; 
        }
    }
    return action;
}


Action& operator--(Action& action) {
    if (action == Action::BUY_PROPERTY) {
        action = static_cast<Action>(static_cast<int>(Action::REDEEM_PLEDGE)); 
    }
    else {
        action = static_cast<Action>(static_cast<int>(action) - 1);
    }
    return action;
}
