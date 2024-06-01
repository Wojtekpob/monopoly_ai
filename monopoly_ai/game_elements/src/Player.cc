#include "Player.h"
#include <stdexcept>
#include <cmath>

std::vector<sf::Color> Player::colors_ = {
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Yellow
};

Player::Player(std::shared_ptr<sf::RenderWindow> win, std::shared_ptr<BoardSquare> startSquare, sf::Vector2f& position_bias, int id, std::shared_ptr<int> current_player)
    : Drawable(win), currentSquare_(startSquare), position_(0), position_bias_(position_bias), id_(id), money_(1500),
    railroads_(0), utilities_(0), current_player_(current_player), start_time_(std::chrono::steady_clock::now()) {
    circle_.setRadius(5.0f); 
    setColor(colors_[id]);
    circle_.setOrigin(circle_.getRadius(), circle_.getRadius()); 
    setPosition(currentSquare_->getPosition());
    circle_.setOutlineColor(sf::Color::White);
    circle_.setOutlineThickness(1.0f);
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
        if (*current_player_ == id_) {
            sf::Vector2f playerPosition = getPosition();

            auto currentTime = std::chrono::steady_clock::now();
            std::chrono::duration<float> elapsedTime = currentTime - start_time_;
            float offsetY = 10.0f * std::sin(elapsedTime.count());

            sf::ConvexShape arrow;
            arrow.setPointCount(7);

            arrow.setPoint(0, sf::Vector2f(0.0f, 0.0f));
            arrow.setPoint(1, sf::Vector2f(30.0f, 0.0f));
            arrow.setPoint(2, sf::Vector2f(30.0f, 20.0f));
            arrow.setPoint(3, sf::Vector2f(50.0f, 20.0f));
            arrow.setPoint(4, sf::Vector2f(25.0f, 50.0f));
            arrow.setPoint(5, sf::Vector2f(0.0f, 20.0f));
            arrow.setPoint(6, sf::Vector2f(20.0f, 20.0f));

            arrow.setFillColor(sf::Color(0, 255, 0, 128));
            arrow.setOutlineColor(sf::Color::Black);
            arrow.setOutlineThickness(2.0f);

            arrow.setPosition(playerPosition.x - 25.0f, playerPosition.y - 70.0f + offsetY);

            window_->draw(arrow);
        }
    }
}

void Player::move(int steps, const std::vector<std::shared_ptr<BoardSquare>>& boardSquares) {
    if (position_ + steps > boardSquares.size()) increaseMoney(400);
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

sf::Vector2f Player::getPosition() {
    return circle_.getPosition();
}