/*
 * This file defines the Action enum class, representing various actions that can be taken in a game.
 * The actions include buying property, paying rent, paying tax, buying houses and hotels, pledging and redeeming properties, and ending a turn.
 * The file also includes overloaded operators for incrementing (++) and decrementing (--) the Action enum values to cycle through the actions.
 */

#ifndef ACTION_H
#define ACTION_H

enum class Action {
    BUY_PROPERTY,
    PAY_RENT,
    PAY_TAX,
    BUY_HOUSE,
    BUY_HOTEL,
    PLEDGE_PROPERTY,
    REDEEM_PLEDGE,
    END 
};


Action& operator++(Action& action);
Action& operator--(Action& action);
#endif 
