#ifndef TAXFIELD_H
#define TAXFIELD_H

#include "ActionField.h"

class TaxField : public ActionField {
public:
    TaxField(int id, const std::string& name, int taxAmount);

    void invokeAction(std::shared_ptr<Player> player) override;

private:
    int taxAmount_;
};

#endif // TAXFIELD_H
