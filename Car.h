#ifndef CAR_H
#define CAR_H

#include <SDL2/SDL.h>
#include "TrafficLight.h"

class Car {
public:
    Car(SDL_Renderer* renderer, int x, int y, int width, int height, int speed);
    void Update(TrafficLight trafficLight);
    void Render();

private:
    SDL_Renderer* renderer;
    int x, y, width, height;
    int speed;
    int roadWidth;
};

#endif
