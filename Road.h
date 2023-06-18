#ifndef ROAD_H
#define ROAD_H

#include <SDL2/SDL.h>

class Road {
public:
    Road(SDL_Renderer* renderer, int x, int y, int width, int height);
    void Render();

private:
    SDL_Renderer* renderer;
    int x, y, width, height;
};

#endif
