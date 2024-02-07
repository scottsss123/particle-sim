#include <SFML/Graphics.hpp>

const int WIDTH = 400;
const int HEIGHT = 400;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "particle-sim");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}