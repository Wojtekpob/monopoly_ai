﻿#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Board.h"
#include "Dice.h"

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
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                board.runRound();
            }
        }
        
        window->clear();
        board.draw();

        window->display();
    }
    return 0;
}

