#include <SFML/Graphics.hpp>
#include <iostream>

#include "Element.h"

int WIDTH = 400;
int HEIGHT = 400;

int main()
{
    std::cout << "hello world\n";

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "particle-sim");
    Element element(10, 10);

    
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        window.draw(element.cell);
        window.display();
    }

    std::cout << "sfml success!\n";
    return 0;
}