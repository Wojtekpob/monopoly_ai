#include "fields/Estate.h"
#include <iostream>
Estate::Estate(int id, const std::string& name, int cost, int houseCost, int hotelCost, std::vector<int> houses_rent, std::string province) 
    : Property(id, name, cost), hotels_(0), houses_(0), houseCost_(houseCost), hotelCost_(hotelCost), houses_rent_(houses_rent), province_(province) {}

void Estate::invokeAction(std::shared_ptr<Player> player) {
    if (owner_) {
        if (player == owner_) {
            player->decreaseMoney(houses_rent_[houses_ + hotels_]);
        }
    }
}
bool Estate::isActionAvailable(std::shared_ptr<Player> player, Action& action) {
    switch (action) { 
    case Action::BUY_PROPERTY:
        return owner_ == nullptr && player->getMoney() >= houses_rent_.front();
    case Action::PAY_RENT:
        return owner_ != nullptr && player != owner_;
    case Action::BUY_HOUSE:
        return owner_ != nullptr && player == owner_ && player->getMoney() >= houses_rent_[houses_ + hotels_];
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