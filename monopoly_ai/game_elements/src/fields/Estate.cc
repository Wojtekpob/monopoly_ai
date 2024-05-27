#include "fields/Estate.h"
#include <iostream>
Estate::Estate(int id, const std::string& name, int cost, int houseCost, int hotelCost, std::vector<int> houses_rent, std::string province) 
    : Property(id, name, cost), hotels_(0), houses_(0), houseCost_(houseCost), hotelCost_(hotelCost), houses_rent_(houses_rent), province_(province) {}

void Estate::invokeAction(std::shared_ptr<Player> player) {
    if (owner_) {
        if (player == owner_) {
            if (houses_ < 4) buyHouse(player);
            else buyHotel(player);
        }
        else {
            payRent(player);
        }
    }
    else {
        buy(player);
    }
}
bool Estate::isActionAvailable(std::shared_ptr<Player> player, Action action) {
    switch (action) { 
    case Action::BUY_PROPERTY:
        return owner_ == nullptr && player->getMoney() >= houses_rent_.front();
    case Action::PAY_RENT:
        return owner_ != nullptr && player != owner_;
    case Action::BUY_HOUSE:
        return owner_ != nullptr && player == owner_ && houses_ < 4 && player->getMoney() >= houseCost_;
    case Action::BUY_HOTEL:
        return owner_ != nullptr && player == owner_ && houses_ == 4 && player->getMoney() >= houses_rent_.back(); 
    case Action::PLEDGE_PROPERTY:
        return owner_ != nullptr && player == owner_ && !pledged_;
    case Action::REDEEM_PLEDGE:
        return owner_ != nullptr && player == owner_ && !pledged_ && player->getMoney() > getRedeemPledgePrice();
    default:
        return false;
    }
}

void Estate::buyHouse(std::shared_ptr<Player> player) {
    if (isActionAvailable(player, Action::BUY_HOUSE)) {
        player->decreaseMoney(houseCost_);
        ++houses_;
    }
}

void Estate::buyHotel(std::shared_ptr<Player> player) {
    if (isActionAvailable(player, Action::BUY_HOTEL)) {
        player->decreaseMoney(hotelCost_);
        ++hotels_;
    }
}

void Estate::payRent(std::shared_ptr<Player> player) {
    if (isActionAvailable(player, Action::PAY_RENT)) {
        player->decreaseMoney(houses_rent_[houses_ + hotels_]);
    }
}