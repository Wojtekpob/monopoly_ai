#ifndef UTILITYFIELD_H
#define UTILITYFIELD_H

#include "Property.h"

class UtilityField : public Property {
public:
    UtilityField(int id, const std::string& name, int cost);

    void invokeAction(std::shared_ptr<Player> player) override;
};

#endif // UTILITYFIELD_H
