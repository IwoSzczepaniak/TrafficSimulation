#ifndef CAR_H
#define CAR_H

#include <SDL2/SDL.h>
#include "TrafficLight.h"

class Car {
public:
    enum Direction {up,down,left,right};


    Car(SDL_Renderer* renderer, int x, int y, int width, int height, int speed);
    void Update(int state);
    void Render();
    void SetOnCrossroad(bool onCrossroad) { this->onCrossroad = onCrossroad; }
    void SetDirection(Direction direction) { this->direction = direction; }
    void SetSpeed(int speed) { this->speed = speed; }

private:
    SDL_Renderer* renderer;
    int x, y, width, height;
    int speed;
    int roadWidth,roadHeight;
    Direction direction;
    bool onCrossroad;
};

#endif
