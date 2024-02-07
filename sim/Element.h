#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <SFML/Graphics.hpp>

class Element
{
public:
    std::string Type = "non";
    int Col[3] = {0, 0, 0};
    sf::RectangleShape Rect;
};

#endif