#include <iostream>

#include "Car.h"
#include "TrafficLight.h"

Car::Car(SDL_Renderer* renderer, int x, int y, int width, int height, int speed)
    : renderer(renderer), x(x), y(y), width(width), height(height), speed(speed), roadWidth(800), roadHeight(600) {}

void Car::Update(int state) {
    srand(time(NULL));
    if (state ==  1) {
        // if (onCrossroad) {
        //     horizontal = !horizontal;
        //     if (rand() % 2 == 0) speed *= -1;
        // }
        switch (direction)
        {
        case up:
            y -= speed;
            break;
        case down:
            y += speed;
            break;
        case left:
            x -= speed;
            break;
        case right:
            x += speed;
            break;
        default:
            break;
        }
    }
}

void Car::Render() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_Rect carRect = { x, y, width, height};
    SDL_RenderFillRect(renderer, &carRect);
}

