#include <SFML/Graphics.hpp>
#include <iostream>

#include "Element.h"

int WIDTH = 400;
int HEIGHT = 400;

int main()
{
    std::cout << "hello world\n";

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "particle-sim");
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    std::cout << "sfml success!\n";

    Element element; 

    return 0;
}