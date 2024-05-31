#include "Player.h"
#include <stdexcept>


Player::Player(std::shared_ptr<sf::RenderWindow> win, std::shared_ptr<BoardSquare> startSquare, sf::Vector2f& position_bias, int id)
    : Drawable(win), currentSquare_(startSquare), position_(0), position_bias_(position_bias), id_(id), money_(1500),
    railroads_(0), utilities_(0) {
    circle_.setRadius(5.0f); 
    setColor(sf::Color(255 / 4 * id, 255 / 4 * id, 255 / 4 * id));
    circle_.setOrigin(circle_.getRadius(), circle_.getRadius()); 
    setPosition(currentSquare_->getPosition());

}

void Player::setColor(sf::Color& color) {
    color_ = color;
    circle_.setFillColor(color);
}

sf::Color Player::getColor() {
    return color_;
}

void Player::setPosition(sf::Vector2f pos) {
    circle_.setPosition(pos + position_bias_);
}

void Player::draw() {
    if (window_) {
        window_->draw(circle_);
    }
}

void Player::move(int steps, const std::vector<std::shared_ptr<BoardSquare>>& boardSquares) {
    position_ = (position_ + steps) % boardSquares.size();
    currentSquare_ = boardSquares[position_];
    setPosition(currentSquare_->getPosition());
}

std::shared_ptr<BoardSquare> Player::getCurrentSquare() const {
    return currentSquare_;
}

bool Player::operator==(const Player& other) const {
    return id_ == other.id_; 
}

void Player::decreaseMoney(int amount) {
    if (money_ < amount) {
        throw std::runtime_error("Not enough money");
    }
    money_ -= amount;
}

void Player::increaseMoney(int amount) {
    money_ += amount;
}

int Player::getMoney() const {
    return money_;
}

void Player::addProperty(int property) {
    properties_.push_back(property);
}

int Player::getRailRoads() {
    return railroads_;
}

void Player::incrementRailRoads() {
    if (railroads_ < 4) ++railroads_;
    else throw std::runtime_error("Can't have more than 4 railroads");
}

int Player::getUtilities() {
    return utilities_;
}

void Player::incrementUtilities() {
    if (utilities_ < 4) ++utilities_;
    else throw std::runtime_error("Can't have more than 4 utilities");
}

std::string Player::to_string() const {
    return "Player " + std::to_string(id_);
}

std::vector<int> Player::getProperties() {
    return properties_;
}