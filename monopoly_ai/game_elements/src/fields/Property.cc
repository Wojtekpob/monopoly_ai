#include <iostream>
#include "fields/Property.h"

Property::Property(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer, int cost)
    : ActionField(id, name, color, textRenderer), pledged_(false), owner_(nullptr), cost_(cost), rent_paid_(false) {}

std::string Property::getStr(Action action) {
    std::string str;
    str += ActionField::getStr(action) + "\n";
    if (owner_) str += "Wlasciciel: " + owner_->to_string();
    else str += "Cena: " + std::to_string(cost_) + "$";
    return str;
}

void Property::buy(std::shared_ptr<Player> player) {
    if (player->getMoney() > cost_) {
        player->decreaseMoney(cost_);
        owner_ = player;
        player->addProperty(id_);
        textRenderer_->addCommunicat(player->to_string() + " kupil " + name_);
        owned_ = true;
        owner_color_ = player->getColor();
    }
    else std::cout << "Brak pieniêdzy" << std::endl;
}

void Property::pledge(std::shared_ptr<Player> player) {
    if (player == owner_ && !pledged_) {
        player->increaseMoney(getPledgePrice());
        pledged_ = true;
        textRenderer_->addCommunicat(player->to_string() + " zastawil " + name_);
    }
    else std::cout << "Player has to be an owner to pledge property" << std::endl;
}

void Property::redeemPledge(std::shared_ptr<Player> player) {
    if (player == owner_ && player->getMoney() > getRedeemPledgePrice() && pledged_) {
        player->decreaseMoney(getRedeemPledgePrice());
        pledged_ = false;
        textRenderer_->addCommunicat(player->to_string() + " wykupil zastaw " + name_);
    }
    else std::cout << "Player has to be an owner to redeem property" << std::endl;
}

int Property::getRedeemPledgePrice() {
    return getPledgePrice() * 1.1;
}

int Property::getPledgePrice() {
    return cost_ / 2;
}

void Property::nextRound() {
    rent_paid_ = false;
}

Action Property::getMandatoryAction(std::shared_ptr<Player> player) {

    if (owner_ && player != owner_ && !pledged_ && !rent_paid_) {
        textRenderer_->addCommunicat("Musisz zaplacic czynsz!");
        return Action::PAY_RENT;
    }
    else return ActionField::getMandatoryAction(player);
}

std::string Property::getDescription() {
    return ActionField::getDescription() + " | Cena: " + std::to_string(cost_) + " | Zastaw/Wykup: " + std::to_string(getPledgePrice()) +
        " / " + std::to_string(getRedeemPledgePrice());
}

void Property::clearProperty() {
    owner_ = nullptr;
    owned_ = false;
    owner_color_ = sf::Color::Black;
    pledged_ = false;
}
