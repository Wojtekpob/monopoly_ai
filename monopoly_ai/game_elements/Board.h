#include <SFML/Graphics.hpp>
#include <memory>
#include "BoardSquare.h"
#include "Drawable.h"

class Board : public Drawable {
private:
    sf::RectangleShape shape_;
    std::vector<BoardSquare> squares_;
public:

    Board( float width, float height, std::shared_ptr<sf::RenderWindow> win );

    virtual void draw() override;

    void initializeSquares( float pos_x, float pos_y );
    void setPosition( float x, float y );
};