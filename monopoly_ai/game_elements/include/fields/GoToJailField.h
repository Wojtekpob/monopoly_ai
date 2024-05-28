#ifndef GOTOJAILFIELD_H
#define GOTOJAILFIELD_H

#include "ActionField.h"

class GoToJailField : public ActionField {
public:
    GoToJailField(int id, const std::string& name);
    bool isActionAvailable(std::shared_ptr<Player> player, Action action) override;
    void invokeAction(std::shared_ptr<Player> player) override;
    void nextRound() override {};
};

#endif // GOTOJAILFIELD_H
