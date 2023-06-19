#include <iostream>

#include "Car.h"

Car::Car(SDL_Renderer* renderer, int x, int y, int width, int height, int speed,
    int layoutWidth, int layoutHeight){
    this->renderer = renderer;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->speed = rand() % 3 + 1;
    this->layoutWidth = layoutWidth;
    this->layoutHeight = layoutHeight;

    // random direction
    int random = rand() % 4;
    switch (random) {
        case 0:
            this->direction = Direction::up;
            break;
        case 1:
            this->direction = Direction::down;
            break;
        case 2:
            this->direction = Direction::left;
            break;
        case 3:
            this->direction = Direction::right;
            break;
    }
}


void Car::Render() {
    SDL_Rect carRect = { x, y, width/2, height/2};
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderFillRect(renderer, &carRect);
}

void Car::Move(int state) {
    switch (direction) {
        case Direction::up:
            if (state == 0) y -= speed;
            break;
        case Direction::down:
            if (state == 0) y += speed;
            break;
        case Direction::left:
            if (state == 1) x -= speed;
            break;
        case Direction::right:
            if (state == 1) x += speed;
            break;
    }
    
}


void Car::DecideDirection(bool canGoUp, bool canGoDown, bool canGoLeft, bool canGoRight, bool isX) {

    // Randomly choose a new direction that the car can go
    std::vector<Direction> possibleDirections;
    possibleDirections.clear();
    if (canGoUp and rand()%2 == 0) {
        if(direction != down) possibleDirections.push_back(Direction::up);
    }
    if (canGoDown and rand()%2 == 0 ) {
        if (direction != up) possibleDirections.push_back(Direction::down);
    }
    if (canGoLeft and rand()%2 == 0) {
        if(direction != right) possibleDirections.push_back(Direction::left);
    }
    if (canGoRight and rand()%2 == 0) {
        if(direction != left) possibleDirections.push_back(Direction::right);
    }

    // if(isX) {
    //     if (direction == up) {
    //         if (canGoLeft && rand()%2 == 0) possibleDirections.push_back(Direction::left);
    //         if (canGoRight && rand()%2 == 0) possibleDirections.push_back(Direction::right);
    //     } else if (direction == down) {
    //         if (canGoLeft && rand()%2 == 0) possibleDirections.push_back(Direction::left);
    //         if (canGoRight && rand()%2 == 0) possibleDirections.push_back(Direction::right);
    //     } else if (direction == left) {
    //         if (canGoUp && rand()%2 == 0) possibleDirections.push_back(Direction::up);
    //         if (canGoDown && rand()%2 == 0) possibleDirections.push_back(Direction::down);
    //     } else if (direction == right) {
    //         if (canGoUp && rand()%2 == 0) possibleDirections.push_back(Direction::up);
    //         if (canGoDown && rand()%2 == 0) possibleDirections.push_back(Direction::down);
    //     }
    // }

    if (!possibleDirections.empty()) {
        // Choose a random direction from the available directions
        int randomIndex = rand() % possibleDirections.size();
        Direction newDirection = possibleDirections[randomIndex];
        SetDirection(newDirection);
    }

        
    

}

