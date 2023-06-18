#include <iostream>

#include "Car.h"
#include "TrafficLight.h"
#include "common.h"

Car::Car(SDL_Renderer* renderer, int x, int y, int width, int height, int speed)
    : renderer(renderer), x(x), y(y), width(width), height(height), speed(speed), 
    roadWidth(WINDOW_WIDTH), roadHeight(WINDOW_HEIGHT) {}

void Car::Update(bool mapState) {
    // srand(time(NULL));
    // if (mapState) {
    //     if (direction == left && x > 0)
    //         x -= speed;
    //     else if (direction == right && x + width < roadWidth)
    //         x += speed;
    // }
    // else {
    //     if (direction == up && y > 0)
    //         y -= speed;
    //     else if (direction == down && y + height < roadHeight)
    //         y += speed;
    // }
}


void Car::Render() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_Rect carRect = { x, y, width, height};
    SDL_RenderFillRect(renderer, &carRect);
}

void Car::onCrossroad(int i, int height, int j, int width){
    // std::cout << "onCrossroad" << std::endl;
    // if (i == 0 && j == 0){
    //     if (direction == up) direction = right;
    //     else if (direction == left) direction = down;
    // }
    // else if(i == height - 1 && j == 0){
    //     if (direction == down) direction = right;
    //     else if (direction == left) direction = up;
    // }
    // else if(i == 0 && j == width - 1){
    //     if (direction == up) direction = left;
    //     else if (direction == right) direction = down;
    // }
    // else if(i == height - 1 && j == width - 1){
    //     if (direction == down) direction = left;
    //     else if (direction == right) direction = up;
    // }


    // else{
    //     if(direction==up or direction == down){
    //         if (rand() % 2 == 0) direction = left; 
    //         else direction = right;
    //     }
    //     if (direction == left or direction == right){
    //         if (rand() % 2 == 0) direction = up;
    //         else direction = down;
    //     }
    // }
}
