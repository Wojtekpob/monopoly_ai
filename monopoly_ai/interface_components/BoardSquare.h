#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class BoardSquare : public Drawable {
private:
    sf::RectangleShape shape;  // Shape to represent the board square
    sf::Text text_;             // Text to display in the square
    float orientation_;           // Orientation of the square (0 = default, 1 = rotated 90 degrees, etc.)

public:
    // Constructor with parameters for width, height, window, orientation, and text
    BoardSquare(float width, float height, std::shared_ptr<sf::RenderWindow> win,
        float orientation, const std::string& textContent);

    virtual void draw(float posX, float posY) override;
};