#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "game_elements/Board.h"
#include "game_elements/Dice.h"

#define SFML_STATIC

using namespace std;

int main()
{
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Board Example");
    Board board(400, 400, window);
    board.setPosition(200.0f, 100.0f);
    Dice dice(window);
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                dice.throwDice();
                std::cout << "Dice value: " << dice.getValue() << std::endl;
            }
        }
        
        window->clear();
        board.draw();
        dice.draw();

        window->display();
    }
    return 0;
}
