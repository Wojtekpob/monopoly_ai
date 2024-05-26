#ifndef PROPERTY_H
#define PROPERTY_H

#include "ActionField.h"

class Property : public ActionField {
public:
    Property(int id, const std::string& name, int cost);

    void buy(std::shared_ptr<Player> player);
    void pledge(std::shared_ptr<Player> player);
    void redeemPledge(std::shared_ptr<Player> player);

private:
    bool pledged_;
    std::shared_ptr<Player> owner_;
    int cost_;
};

#endif // PROPERTY_H
