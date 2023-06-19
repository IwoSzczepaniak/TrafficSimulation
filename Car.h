#ifndef CAR_H
#define CAR_H

#include <SDL2/SDL.h>
#include "common.h"
#include <vector>


class Car {
public:
    enum Direction {up,down,left,right};


    Car(SDL_Renderer* renderer, int x, int y, int width, int height, int speed,
    int layoutWidth, int layoutHeight);
    void Move(int state);
    void DecideDirection(bool canGoUp, bool canGoDown, bool canGoLeft, bool canGoRight, bool isX);

    void Render();

    void SetDirection(Direction direction) { this->direction = direction; }
    void SetSpeed(int speed) { this->speed = speed; }
    int GetX() { return x; }
    int GetY() { return y; }


private:
    SDL_Renderer* renderer;
    int x, y, width, height, layoutWidth, layoutHeight;
    int speed;
    int roadWidth,roadHeight;
    std::vector<std::vector<char>> grid;
    Direction direction;
};

#endif
