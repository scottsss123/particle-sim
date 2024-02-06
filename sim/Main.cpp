#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <time.h>

const int WIDTH = 400;
const int HEIGHT = 400;
const int scl = 5;
const int wRes = WIDTH / scl;
const int hRes = HEIGHT / scl;

enum element { none, sand, water, steam, wall };
std::vector<std::vector<int>> eColours = {{0,0,0}, {230,220,110}, {50,50,250}, {200,200,200}};
element currentElement = sand;

class Cell
{
public:
    int Pos[2];
    int Size = scl;
    float density;
    element Type;
    bool moveableSolid;
    sf::RectangleShape Rect;

    Cell(int x, int y, element type) 
    {
        Pos[0] = x;
        Pos[1] = y;

        Type = type;

        if (Type == sand) 
            density = 1;
        else if (Type == water)
            density = 0.5;
        else if (Type == steam)
            density = -1;

        Rect.setSize(sf::Vector2f(scl,scl));
        Rect.setPosition(x*scl, y*scl);
        Rect.setFillColor(sf::Color(eColours.at(Type)[0], eColours.at(Type)[1], eColours.at(Type)[2]));
    }

    void Update();
};

std::vector<std::vector<Cell>> grid;

void Cell::Update()
{
    if (Type == none)
        return;
        
    int nextPos[2] = {Pos[0], Pos[1]};

    if (density > 0) 
    {
        nextPos[1]++;
    } else if (density < 0)
    {
        nextPos[1]--;
    } 

    if (nextPos[1] >= 0 && nextPos[1] < hRes){
        if (grid[nextPos[1]][nextPos[0]].Type == none)
        {
            Cell temp = grid[nextPos[1]][nextPos[0]];
            grid[nextPos[1]][nextPos[0]] = grid[Pos[1]][Pos[0]];
            grid[Pos[1]][Pos[0]] = temp;
            return;
        }
    }

    srand(time(0));
    int ranChoice = rand() % 2;
}

bool mousePressed = false;

int main()
{
    for (int i = 0; i < hRes; i++)
    {
        std::vector<Cell> row;
        for (int j = 0; j < wRes; j++)
        {
            Cell cell(j, i, none);
            row.push_back(cell);
        }
        grid.push_back(row);
    }

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "particle-sim"); 

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                mousePressed = true;
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                mousePressed = false;
            }
        }
      
        window.clear(sf::Color::Black);

        if (mousePressed) 
        {
            int x = std::floor(sf::Mouse::getPosition(window).x / scl);
            int y = std::floor(sf::Mouse::getPosition(window).y / scl);
            std::cout << "[ " << x << ", " << y << " ]" << std::endl;
            if ( x >= 0 && x < wRes && y >= 0 && y < hRes)
            {
                Cell add_cell(x, y, currentElement);
                grid.at(y).at(x) = add_cell;
            }
        }

        for (int i = 0; i < hRes; i++)
        {
            for (int j = 0; j < wRes; j++)
            {
                window.draw(grid.at(i).at(j).Rect);
            }
        }

        for (int i = hRes - 1; i > -1; i--)
        {
            for (int j = wRes - 1; j > -1; j--)
            {
                grid[i][j].Update();
            }
        }

        window.display();
    }

    std::cout << "sfml success!\n";
    return 0;
}