#include "fields/TaxField.h"
#include <iostream>

TaxField::TaxField(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer, int taxAmount)
    : ActionField(id, name, color, textRenderer), taxAmount_(taxAmount), paid_(false) {}

void TaxField::invokeAction(std::shared_ptr<Player> player) {
    if (isActionAvailable(player, Action::PAY_TAX)) {
        player->decreaseMoney(taxAmount_);
        paid_ = true;
        textRenderer_->addCommunicat(player->to_string() + " zaplacil podatek = " + std::to_string(taxAmount_));
    }
}

bool TaxField::isActionAvailable(std::shared_ptr<Player> player, Action action) {
    switch (action) {
    case Action::PAY_TAX:
        return !paid_ && player->getMoney() >= taxAmount_;
    default:
        return ActionField::isActionAvailable(player, action);
    }
}

std::string TaxField::getStr(Action action) {
    std::string str;
    str += ActionField::getStr(action) + "\n";
    return str + "Podatek: " + std::to_string(taxAmount_);
}

void TaxField::nextRound() {
    paid_ = false;
}

std::string TaxField::getDescription() {
    return ActionField::getDescription() + " | Podatek: " + std::to_string(taxAmount_);
}

Action TaxField::getMandatoryAction(std::shared_ptr<Player> player) {
    if (!paid_)
    {
        textRenderer_->addCommunicat("Musisz zaplacic podatek = " + std::to_string(taxAmount_) + "!");
        return Action::PAY_TAX;
    }
    else return ActionField::getMandatoryAction(player);
}