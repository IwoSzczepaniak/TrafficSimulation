#ifndef CAR_H
#define CAR_H

#include <SDL2/SDL.h>
#include "TrafficLight.h"

class Car {
public:
    enum Direction {up,down,left,right};


    Car(SDL_Renderer* renderer, int x, int y, int width, int height, int speed);
    void Update(bool mapState);
    void Render();
    void SetDirection(Direction direction) { this->direction = direction; }
    void SetSpeed(int speed) { this->speed = speed; }
    int GetX() { return x; }
    int GetY() { return y; }

    void onCrossroad(int i, int height, int j, int width);

private:
    SDL_Renderer* renderer;
    int x, y, width, height;
    int speed;
    int roadWidth,roadHeight;
    Direction direction;
};

#endif
