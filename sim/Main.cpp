#include <SDL2/SDL.h>
#include <iostream>
#include <unordered_map>

#define res        1
#define SW         50 * res
#define SH         50 * res
#define MGI        SW * SH
#define pixelScale 10 / res
#define SDLSW      (SW * pixelScale)
#define SDLSH      (SH * pixelScale)

enum type {
    empty,
    sand,
    water,
    wall
}; type ct; int nTypes = 4;
int density[] = {
    1,
    10,
    5,
    100
};
struct timer {
    int fr1, fr2;
}; timer T;
struct element {
    type t;
    int d;
    int x, y;
}; 

std::unordered_map<int, element> g;
std::unordered_map<int, element> ng;

bool mouseDown = false;
int brushSize = 4;
int mx, my;

void pixel(int x, int y, int c, SDL_Renderer* renderer)
{
    int rgb[3];
    if (c == 1) { rgb[0] = 246; rgb[1] = 215; rgb[2] = 176; }      //SAND
    if (c == 2) { rgb[0] = 20;  rgb[1] = 20;  rgb[2] = 200; }      //WATER
    if (c == 3) { rgb[0] = 200; rgb[1] = 200; rgb[2] = 200; }      //WALL
    if (c == 0) { rgb[0] = 0;   rgb[1] = 0;   rgb[2] = 0;   }      //BACKGROUND

    SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
    SDL_Rect pix;
    pix.w = pixelScale;
    pix.h = pixelScale;
    pix.x = pixelScale * x;
    pix.y = pixelScale * y;
    SDL_RenderFillRect(renderer, &pix);
}

void clearBackground(SDL_Renderer* renderer)
{ int y, x;
    for (y = 0; y < SH; y++)
    {
        for (x = 0; x < SW; x++)
        {
            pixel(x, y, 0, renderer);
        }
    }
}

void drawElements(SDL_Renderer* renderer)
{ int i;
    for (i = 0; i < (SW * SH); i++)
    {
        pixel(g[i].x, g[i].y, (int)g[i].t, renderer);
    }
}

void drawBrush(SDL_Renderer* renderer)
{
    SDL_Rect b;
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    b.x = (mx * pixelScale) - ( (0.5 * brushSize) * pixelScale );
    b.y = (my * pixelScale) - ( (0.5 * brushSize) * pixelScale );
    b.w = brushSize * pixelScale;   b.h = brushSize * pixelScale;
    SDL_RenderDrawRect(renderer, &b);
}

void swap(element e1, element e2, int i1, int i2)
{
    int tx = e1.x;  int ty = e1.y;
    e1.x = e2.x;    e1.y = e2.y;
    e2.x = tx;      e2.y = ty;
    element te = e1;
    ng[i1] = e2;
    ng[i2] = te;
}

void addElements(int x1, int y1, int x2, int y2, type t)
{ int y; int x;
    if (x1 < 0)     { x1 = 0; } 
    if (x2 > SW-1)  { x2 = SW-1; }
    if (y1 < 0)     { y1 = 0; }
    if (y2 > SH-1)  { y2 = SH-1; }

    for (y=y1; y<y2; y++)
    {
        for (x=x1; x<x2; x++)
        {
            element e;
            e.t = t;
            e.x = x;    e.y = y;
            e.d = density[(int)e.t];
            g[x + (SW * y)] = e;
        }
    }
}

void update()
{ int y, x;
    ng = g;
    for (y = 0; y < SH; y++)
    {
        for (x = 0; x < SW; x++)
        {
            int i = x + (SW * y);
            if (g[i].t == 0) { continue; }         //EMPTY
            if (g[i].t == 1) {                      //SAND
                //down
                int di = i + SW;
                int ni = di;
                if ( ni < MGI ) {
                    if (ng[ni].t == 0 || ng[ni].d < g[i].d) { swap(g[i], ng[ni], i, ni); continue; }
                    //diagonal
                    int d1 = (rand() > RAND_MAX) ? 1 : -1;
                    int d2 = -1 * d1;
                    if (x + d1 > 0 && x + d1 < SW) {
                        ni = di + d1;
                        if (ng[ni].t == 0 || ng[ni].d < g[i].d) { swap(g[i], ng[ni], i, ni); continue; }
                    }
                    if (x + d2 > 0 && x + d2 < SW) {
                        ni = di + d2;
                        if (ng[ni].t == 0 || ng[ni].d < g[i].d) { swap(g[i], ng[ni], i, ni); continue; }
                    }
                }
            }
            if (g[i].t == 2) {                      //WATER

                //down
                int di = i + SW;
                int ni = di;
                if ( ni < MGI ) {
                    if (ng[ni].t == 0 || ng[ni].d < g[i].d) { swap(g[i], ng[ni], i, ni); continue; }
                    //diagonal
                    int d1 = (rand() > RAND_MAX) ? 1 : -1;
                    int d2 = -1 * d1;
                    if (x + d1 > 0 && x + d1 < SW) {
                        ni = di + d1;
                        if (ng[ni].t == 0 || ng[ni].d < g[i].d) { swap(g[i], ng[ni], i, ni); continue; }
                    }
                    if (x + d2 > 0 && x + d2 < SW) {
                        ni = di + d2;
                        if (ng[ni].t == 0 || ng[ni].d < g[i].d) { swap(g[i], ng[ni], i, ni); continue; }
                    }
                    //side
                    if (x + d1 > 0 && x + d1 < SW)
                    {
                        ni = i + d1;
                        if (ng[ni].t == 0 || ng[ni].d < g[i].d) { swap(g[i], ng[ni], i, ni); continue; }
                    }
                    if (x + d2 > 0 && x + d2 < SW)
                    {
                        ni = i + d2;
                        if (ng[ni].t == 0 || ng[ni].d < g[i].d) { swap(g[i], ng[ni], i, ni); continue; }
                    }
                }
            }
            if (g[i].t == 3) { continue; }          //wall
        }
    }  
    g = ng;  
}

void display(SDL_Renderer* renderer)
{
    if (T.fr1 - T.fr2 >= 50)
    {
        SDL_GetMouseState(&mx, &my);
        mx /= pixelScale; my /= pixelScale;

        if (mouseDown)
        {            
            addElements(mx - (0.5*brushSize), my - (0.5*brushSize), mx+(0.5*brushSize), my+(0.5*brushSize), ct);
        }

        clearBackground(renderer);
        update();
        drawElements(renderer);
        drawBrush(renderer);

        T.fr2 = T.fr1;
        SDL_RenderPresent(renderer);
    }
    T.fr1 = SDL_GetTicks();
}

void init()
{ int x, y;
    for (y = 0; y < SH; y++)
    {
        for (x = 0; x < SW; x++)
        {
            int index = (SW * y) + x;
            element e;
            e.x = x;
            e.y = y;
            e.t = (type)0;
            g[index] = e;
        }
    }

    ct = sand;
}

int main()
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(SDLSW, SDLSH, 0, &window, &renderer);

    SDL_Event e;
    bool running = true;

    init();

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouseDown = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouseDown = false;
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_UP:
                            if (brushSize <= 16)
                                brushSize *= 2;
                            break;
                        case SDL_SCANCODE_DOWN:
                            if (brushSize >= 2)
                                brushSize /= 2;
                            break;
                        case SDL_SCANCODE_RIGHT:
                            if (ct < nTypes)
                                ct = (type)(ct+1);
                            break;
                        case SDL_SCANCODE_LEFT:
                            if (ct > -1)
                                ct = (type)(ct-1);
                            break;
                    }
                    break;
            }
        }

        display(renderer);
    }

    return 0;
}
