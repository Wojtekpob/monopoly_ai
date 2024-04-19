#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "BoardSquare.h"

class Board : public Drawable {
private:
    sf::RectangleShape shape_;
    std::vector<BoardSquare> squares_;
public:

    Board(float width, float height, std::shared_ptr<sf::RenderWindow> win);

    virtual void draw(float posX, float posY) override;

    void initializeSquares(float posX, float posY);

};