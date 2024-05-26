#ifndef GOTOJAILFIELD_H
#define GOTOJAILFIELD_H

#include "ActionField.h"

class GoToJailField : public ActionField {
public:
    GoToJailField(const std::string& name);

    void invokeAction(std::shared_ptr<Player> player) override;
};

#endif // GOTOJAILFIELD_H
