#ifndef GRID_H
#define GRID_H

#include "Element.h"
#include "Sand.h"
#include <vector>
#include <iostream>

class Grid
{
public:
    int Width;
    int Height;
    
    std::vector<std::vector<Element>> Arr;

    Grid(int width, int height)
    {
        Width = width;
        Height = height;

        for (int y = 0; y < Height; y++)
        {
            std::vector<Element> row;
            for (int x = 0; x < Width; x++)
            {
                Element cell;
                cell.Rect.setSize(sf::Vector2f(1,1));
                row.push_back(cell);
            }
            Arr.push_back(row);
        }
    }

    void AddElement(std::string elementStr, int x, int y)
    {
        if (elementStr == "snd")
        {
            Sand sand;
            Arr[y][x] = sand;
        }
    }
};

#endif