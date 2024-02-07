#ifndef SAND_H
#define SAND_H

#include "Solid.h"
#include <vector>

class Sand: public Solid
{
public:

    Sand()
    {
        Type = "sld";
        Col[0] = 229;
        Col[1] = 221;
        Col[2] = 111;
        Rect.setSize(sf::Vector2f(1,1));
        Rect.setFillColor(sf::Color(229, 221, 111));
    }
    
};

#endif