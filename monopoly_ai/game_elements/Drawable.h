#include <memory>
#include <SFML/Graphics.hpp>
#pragma once
class Drawable {
protected:
    std::shared_ptr<sf::RenderWindow> window_; 

public:

    Drawable(std::shared_ptr<sf::RenderWindow> win) : window_(win) {}
    virtual ~Drawable() {}

    virtual void draw(float posX, float posY) = 0;
};