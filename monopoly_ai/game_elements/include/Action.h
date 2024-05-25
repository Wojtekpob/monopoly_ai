#ifndef ACTION_H
#define ACTION_H

enum class Action {
    BUY_PROPERTY,
    PAY_RENT,
    BUY_HOUSE,
    BUY_HOTEL,
    PLEDGE_PROPERTY,
    PAY_TAX,
    REDEEM_PLEDGE,
    END 
};


Action& operator++(Action& action);
Action& operator--(Action& action);
#endif 
