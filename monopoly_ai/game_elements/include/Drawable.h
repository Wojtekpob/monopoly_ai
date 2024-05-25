#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>
#include <memory>

class Drawable {
public:
    Drawable(std::shared_ptr<sf::RenderWindow> win) : window_(win) {}
    virtual void draw() = 0;

protected:
    std::shared_ptr<sf::RenderWindow> window_;
};

#endif // DRAWABLE_H
