#include "monopoly_ai.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "game_elements/Board.h"
#include <memory>
#define SFML_STATIC

using namespace std;

int main()
{
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Board Example");
    Board board(400, 400, window);
    board.setPosition(200.0f, 100.0f);
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        board.draw();
        window->display();
    }
    return 0;
}
