﻿// monopoly_ai.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "monopoly_ai.h"
#include <SFML/Graphics.hpp>
#define SFML_STATIC

using namespace std;

int main()
{
    
    sf::Window window(sf::VideoMode(800, 600), "my window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
	cout << "Hello CMake." << endl;
	return 0;
}
