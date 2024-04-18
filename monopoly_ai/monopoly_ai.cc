#include "monopoly_ai.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "interface_components/Board.h"
#include <memory>
#define SFML_STATIC

using namespace std;

int main()
{
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Board Example");
    Board board(400, 400, window);  // Pass the shared window pointer to the Board

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        board.draw(200.0f, 100.0f);
        window->display();
    }
    return 0;
}
