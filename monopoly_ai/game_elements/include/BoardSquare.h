#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Drawable.h"
//#include "fields/ActionField.h"


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
