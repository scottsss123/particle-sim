#include <iostream>
#include <SFML/Graphics.hpp>
#include "Element.h"

Element::Element(int x, int y)
{
    std::cout << "Element created!\n";

    cell.setSize(sf::Vector2f(1,1));    
    cell.setPosition(sf::Vector2f(x,y));
    cell.setFillColor(sf::Color::White);
    cell.setOutlineColor(sf::Color::White);
}
