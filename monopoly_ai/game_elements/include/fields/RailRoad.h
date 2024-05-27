#ifndef RAILROAD_H
#define RAILROAD_H

#include "Property.h"

class RailRoad : public Property {
public:
    RailRoad(int id, const std::string& name, int cost, int rent);

    void invokeAction(std::shared_ptr<Player> player) override;

private:
    int rent_;
};

#endif // RAILROAD_H
