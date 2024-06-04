/*
 * This file defines the BoardSquare class, representing a single square on the game board.
 * The BoardSquare class includes methods for setting its position, color, and associated ActionField.
 * It handles the rendering of the square, including its fill color, outline color, and texture if provided.
 * The class inherits from Drawable to allow it to be drawn within the game window.
 * Author: Wojciech Pobocha
 */

#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Drawable.h"

class ActionField;

class BoardSquare : public Drawable {
public:
    BoardSquare(float width, float height, std::shared_ptr<sf::RenderWindow> win,
        float orientation, const std::string& textContent,
        const sf::Color& fillColor, const std::string& textureFile);
    void draw() override;
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void setColor(sf::Color&);
    void setActionField(std::shared_ptr<ActionField> actionField);

    std::shared_ptr<ActionField> actionField_;
private:
    sf::RectangleShape shape_;
    sf::Text text_;
    sf::Texture texture_;
    float orientation_;
    std::shared_ptr<sf::RenderWindow> window_;
};

#endif // BOARDSQUARE_H
