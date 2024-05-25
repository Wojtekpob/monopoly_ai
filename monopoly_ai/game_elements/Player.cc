#include "Player.h"
#include <stdexcept>

Player::Player(std::shared_ptr<sf::RenderWindow> win, std::shared_ptr<BoardSquare> startSquare, sf::Vector2f& position_bias, int id)
    : Drawable(win), currentSquare_(startSquare), position_(0), position_bias_(position_bias), id_(id) {
    circle_.setRadius(5.0f); 
    circle_.setFillColor(sf::Color::White); 
    circle_.setOrigin(circle_.getRadius(), circle_.getRadius()); 
    setPosition(currentSquare_->getPosition());
}

void Player::setPosition(sf::Vector2f &pos) {
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