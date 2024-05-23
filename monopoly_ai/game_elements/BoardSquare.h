#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Drawable.h"

class BoardSquare : public Drawable {
public:
    BoardSquare(float width, float height, std::shared_ptr<sf::RenderWindow> win,
        float orientation, const std::string& textContent,
        const sf::Color& fillColor, const std::string& textureFile);
    void draw() override;
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

private:
    sf::RectangleShape shape_;
    sf::Text text_;
    sf::Texture texture_;
    float orientation_;
    std::shared_ptr<sf::RenderWindow> window_;
};

#endif // BOARDSQUARE_H
