#ifndef ELEMENT_H
#define ELEMENT_H

#include <SFML/Graphics.hpp>

class Element
{
    public:
        sf::RectangleShape cell;

        Element(int x, int y);
};

#endif