#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Board : public Drawable {
private:
    sf::RectangleShape shape_;  // SFML Rectangle Shape to represent the board
    std::vector<sf::RectangleShape> squares_;
public:
    // Constructor with parameters for width, height, and window
    Board(float width, float height, std::shared_ptr<sf::RenderWindow> win);

    virtual void draw(float posX, float posY) override;

    void initializeSquares(float posX, float posY);

};