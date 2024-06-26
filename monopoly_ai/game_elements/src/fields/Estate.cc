#include <iostream>
#include "fields/Estate.h"

Estate::Estate(int id, const std::string& name, sf::Color& color, std::shared_ptr<TextRenderer> textRenderer, int cost, int houseCost, int hotelCost, std::vector<int> houses_rent, std::string province)
    : Property(id, name, color, textRenderer, cost), hotels_(0), houses_(0), houseCost_(houseCost), hotelCost_(hotelCost), houses_rent_(houses_rent),
    province_(province), bought_(false) {}

void Estate::invokeAction(std::shared_ptr<Player> player) {
    if (owner_) {
        if (player == owner_) {
            if (houses_ < 4) {
                buyHouse(player);
                bought_ = true;
            }
            else {
                buyHotel(player);
                std::cout << "Kupiono Hotel" << std::endl;
                bought_ = true;
            }
            }
        else {
            payRent(player);
            std::cout << "Zap�acono czynsz" << std::endl;
        }
    }
    else {
        buy(player);
        bought_ = true;
    }
}

bool Estate::isActionAvailable(std::shared_ptr<Player> player, Action action) {
    switch (action) { 
    case Action::BUY_PROPERTY:
        return owner_ == nullptr && player->getMoney() >= houses_rent_.front();
    case Action::PAY_RENT:
        return owner_ != nullptr && player != owner_ && !pledged_ && !rent_paid_ && player->getMoney() >= houses_rent_[houses_ + hotels_];
    case Action::BUY_HOUSE:
        return owner_ != nullptr && player == owner_ && !bought_ && !pledged_ && houses_ < 4 && player->getMoney() >= houseCost_;
    case Action::BUY_HOTEL:
        return owner_ != nullptr && player == owner_ && !bought_ && !pledged_ && houses_ == 4 && hotels_ == 0 && player->getMoney() >= houses_rent_.back();
    default:
        return ActionField::isActionAvailable(player, action);
    }
}

void Estate::buyHouse(std::shared_ptr<Player> player) {
    if (isActionAvailable(player, Action::BUY_HOUSE)) {
        player->decreaseMoney(houseCost_);
        ++houses_;
        bought_ = true;
        textRenderer_->addCommunicat(player->to_string() + " kupil dom w " + name_);
    }
}

void Estate::buyHotel(std::shared_ptr<Player> player) {
    if (isActionAvailable(player, Action::BUY_HOTEL)) {
        player->decreaseMoney(hotelCost_);
        ++hotels_;
        bought_ = true;
        textRenderer_->addCommunicat(player->to_string() + " kupil hotel w " + name_);
    }
}

void Estate::payRent(std::shared_ptr<Player> player) {
    if (isActionAvailable(player, Action::PAY_RENT)) {
        player->decreaseMoney(houses_rent_[houses_ + hotels_]);
        rent_paid_ = true;
        owner_->increaseMoney(houses_rent_[houses_ + hotels_]);
        textRenderer_->addCommunicat(player->to_string() + " zaplacil czynsz " + owner_->to_string());
    }
}

std::string Estate::getStr(Action action) {
    std::string str;
    str = Property::getStr(action);
    str = str + "\n" + "Cena domu: " + std::to_string(houseCost_) + "\n" + "Cena hotelu: " + std::to_string(hotelCost_);
    if (owner_) {
        str = str + "\n" + "Ilosc domow: " + std::to_string(houses_) + "\nIlosc hoteli: " + std::to_string(hotels_);
        str = str + "\n" + "Czynsz: " + std::to_string(houses_rent_[houses_ + hotels_]);
    }
   return str;
}


void Estate::nextRound() {
    Property::nextRound();
    bought_ = false;
}

int Estate::getHotels() {
    return hotels_;
}
int Estate::getHouses() {
    return houses_;
}

void Estate::clearProperty() {
    houses_ = 0;
    hotels_ = 0;
    bought_ = false;
    Property::clearProperty();
}