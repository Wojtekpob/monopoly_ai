/*
 * This file defines the Drawable class, an abstract base class for drawable objects in the game.
 * The Drawable class requires derived classes to implement the draw method for rendering.
 * It holds a shared pointer to an sf::RenderWindow object, which is used for drawing.
 * Author: Mikołaj Sendybył
 */

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <memory>
#include <SFML/Graphics.hpp>

class Drawable {
public:
    Drawable(std::shared_ptr<sf::RenderWindow> win) : window_(win) {}
    virtual void draw() = 0;

protected:
    std::shared_ptr<sf::RenderWindow> window_;
};

#endif // DRAWABLE_H
