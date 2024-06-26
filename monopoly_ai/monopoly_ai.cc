﻿/*
 * This file contains the main function, which initializes the game window and runs the main game loop.
 * The main function sets up the game board, handles user input for various actions such as rolling dice,
 * performing actions, navigating properties, and surrendering. It uses SFML for rendering and managing events.
 * The game loop continues to process events and render the game until the window is closed.
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Board.h"
#include "Dice.h"
#include "fields/FieldLoader.h"

#define SFML_STATIC

using namespace std;

int main()
{
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1500, 900), "Board Example");
    Board board(400, 400, window);
    board.setPosition(200.0f, 100.0f);
    sf::Color backgroundColor = sf::Color(9, 100, 9);
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (board.game_end_) continue;
            if (!board.property_selection_) {
                if (!board.dice_tossed_ && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    board.runRound();
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                    board.incrementAction();
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                    board.decrementAction();
                }
                else if (board.dice_tossed_ && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    board.nextPlayer();
                }
                else if (board.dice_tossed_ && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I) {
                    board.performCurrentAction();
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) {
                    board.playerSurrender();
                }
            }
            else {
                if (board.dice_tossed_ && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                    board.previousProperty();
                }
                else if (board.dice_tossed_ && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                    board.nextProperty();
                }
                else if (board.dice_tossed_ && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    board.actionOnProperty();
                }
                else if (board.dice_tossed_ && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B) {
                    board.closePropertySelection();
                }
            }
        }
        if (!board.game_end_) {
            window->clear(backgroundColor);
            board.draw();
        }
        window->display();
    }
    return 0;
}

