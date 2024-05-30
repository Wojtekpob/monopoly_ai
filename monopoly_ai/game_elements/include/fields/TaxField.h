#ifndef TAXFIELD_H
#define TAXFIELD_H

#include "ActionField.h"

class TaxField : public ActionField {
public:
    TaxField(int id, const std::string& name, sf::Color& color, int taxAmount);

    void invokeAction(std::shared_ptr<Player> player) override;
    bool isActionAvailable(std::shared_ptr<Player> player, Action action) override;
    std::string getStr(Action action) override;
    void nextRound() override;
    std::string getDescription() override;
    Action getMandatoryAction(std::shared_ptr<Player> player) override;
private:
    int taxAmount_;
    bool paid_;
};

#endif // TAXFIELD_H
