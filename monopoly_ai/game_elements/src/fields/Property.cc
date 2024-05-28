#include "fields/Property.h"
#include <iostream>

Property::Property(int id, const std::string& name, int cost)
    : ActionField(id, name), pledged_(false), owner_(nullptr), cost_(cost) {}

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
        std::cout << "Kupiono " << name_ << std::endl;
    }
    else std::cout << "Brak pieniêdzy" << std::endl;
}

bool Property::isActionAvailable(std::shared_ptr<Player> player, Action action) {
    switch (action) {
    case Action::PLEDGE_PROPERTY:
        return owner_ != nullptr && player == owner_ && !pledged_;
    case Action::REDEEM_PLEDGE:
        return owner_ != nullptr && player == owner_ && pledged_ && player->getMoney() > getRedeemPledgePrice();
    default:
        return false;
    }
}

void Property::pledge(std::shared_ptr<Player> player) {
    if (player == owner_) {
        player->increaseMoney(getPledgePrice());
        pledged_ = true;
    }
    else std::cout << "Player has to be an owner to pledge property" << std::endl;
}

void Property::redeemPledge(std::shared_ptr<Player> player) {
    if (player == owner_ && player->getMoney() > getRedeemPledgePrice()) {
        player->decreaseMoney(cost_ / 2);

    }
    else std::cout << "Player has to be an owner to redeem property" << std::endl;
}

int Property::getRedeemPledgePrice() {
    return getPledgePrice() * 1.1;
}

int Property::getPledgePrice() {
    return cost_ / 2;
}