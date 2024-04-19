#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class BoardSquare : public Drawable {
private:
    sf::Text text_;             
    float orientation_;         

public:
    sf::RectangleShape shape_;
    BoardSquare(float width, float height, std::shared_ptr<sf::RenderWindow> win,
        float orientation, const std::string& textContent);

    virtual void draw() override;
    void setPosition(float x, float y);
};