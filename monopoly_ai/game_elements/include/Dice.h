/*
 * This file defines the Dice class, which represents a game die that can be rolled to generate a random value between 1 and 6.
 * The Dice class includes methods for throwing the die, drawing the die on the screen, and retrieving the current value of the die.
 * It uses SFML for rendering and managing textures for each face of the die. The textures are loaded from files, and the sprite is updated based on the current value.
 * Author: Mikołaj Sendybył
 */

#ifndef DICE_H
#define DICE_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

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
