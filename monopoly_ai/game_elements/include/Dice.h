#ifndef DICE_H
#define DICE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Dice {
public:
    Dice(std::shared_ptr<sf::RenderWindow> window);
    void throwDice();
    void draw();
    int getValue() const;

private:
    void loadTextures();

    std::shared_ptr<sf::RenderWindow> window_;
    sf::Sprite sprite_;
    std::vector<sf::Texture> textures_;
    int value_;
};

#endif // DICE_H