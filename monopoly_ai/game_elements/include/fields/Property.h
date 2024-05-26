#ifndef PROPERTY_H
#define PROPERTY_H

#include "ActionField.h"

class Property : public ActionField {
public:
    Property(const std::string& name, int cost);

    void invokeAction(std::shared_ptr<Player> player) override;

private:
    bool pledged_;
    std::shared_ptr<Player> owner_;
    int cost_;
};

#endif // PROPERTY_H
