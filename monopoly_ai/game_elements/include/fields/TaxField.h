/*
 * This file defines the TaxField class, a subclass of ActionField.
 * The TaxField class represents a game field where players must pay a tax.
 * It includes methods for handling the action of paying tax, checking if the tax payment is available,
 * and managing the tax amount. The class also overrides several methods from ActionField to provide specific behaviors for tax fields.
 * Author: Mikołaj Sendybył
 */

#ifndef TAXFIELD_H
#define TAXFIELD_H

#include "ActionField.h"

class TaxField : public ActionField {
public:
    TaxField(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer, int taxAmount);

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
