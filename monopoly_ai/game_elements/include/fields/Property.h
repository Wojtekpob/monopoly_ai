#ifndef PROPERTY_H
#define PROPERTY_H

#include "ActionField.h"

class Property : public ActionField {
public:
    Property(int id, const std::string& name, int cost);

    void buy(std::shared_ptr<Player> player);
    void pledge(std::shared_ptr<Player> player);
    void redeemPledge(std::shared_ptr<Player> player);
    bool isActionAvailable(std::shared_ptr<Player> player, Action action) override;
    int getRedeemPledgePrice();
    int getPledgePrice();
    std::string getStr(Action action) override;
    void nextRound() override;

protected:
    bool pledged_;
    std::shared_ptr<Player> owner_;
    int cost_;
    bool rent_paid_;
};

#endif // PROPERTY_H
