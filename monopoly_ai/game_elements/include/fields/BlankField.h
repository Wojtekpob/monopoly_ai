#ifndef BLANKFIELD_H
#define BLANKFIELD_H

#include "ActionField.h"

class BlankField : public ActionField {
public:
    BlankField(const std::string& name);

    void invokeAction(std::shared_ptr<Player> player) override;
};

#endif // BLANKFIELD_H
