#include <SFML/Graphics.hpp>
#include <iostream>

#include "Grid.h"

const int WIDTH = 400;
const int HEIGHT = 400;

bool mousePressed = false;
enum element {
    sand
};
element currentElement = sand;

void display(sf::RenderWindow &window, Grid grid)
{
    window.clear(sf::Color::Black);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (grid.Arr[y][x].Type == "non")
                continue;
            
            grid.Arr[y][x].Rect.setPosition(sf::Vector2f(x, y));
            window.draw(grid.Arr[y][x].Rect);
        }
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "particle-sim");
    window.setFramerateLimit(60);

    Grid grid(WIDTH, HEIGHT);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                mousePressed = true;
            if (event.type == sf::Event::MouseButtonReleased)
                mousePressed = false;
        }

        if (mousePressed)
        {
            int x = sf::Mouse::getPosition(window).x;
            int y = sf::Mouse::getPosition(window).y;

            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
            {
                std::cout << "mousePressed() [ " << x << ", " << y << " ]\n";
                if (currentElement == sand)
                    grid.AddElement("snd", x, y);
            }
        }


        display(window, grid);
        window.display();
    }
}