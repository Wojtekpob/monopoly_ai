#ifndef RAILROAD_H
#define RAILROAD_H

#include "Property.h"

class RailRoad : public Property {
public:
    RailRoad(int id, const std::string& name, int cost, int rent);

    void invokeAction(std::shared_ptr<Player> player) override;
    bool isActionAvailable(std::shared_ptr<Player> player, Action action) override;
    int getRent();
    std::string getStr(Action action) override;
    void nextRound() override {};
private:
    int rent_;
};

#endif // RAILROAD_H
