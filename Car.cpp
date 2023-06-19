#include <iostream>

#include "Car.h"

Car::Car(SDL_Renderer* renderer, int x, int y, int width, int height, int speed, std::vector<std::vector<char>> grid,
    int layoutWidth, int layoutHeight){
    this->renderer = renderer;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->speed = rand() % 3 + 1;
    this->grid = grid;
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


void Car::DecideDirection() {
    int i = y / height;
    int j = x / width;

    // Get the available directions at the crossroad based on the road layout
    bool canGoUp = (i > 0 && (grid[i - 1][j] == '|' || grid[i - 1][j] == 'x'));
    bool canGoDown = (i < layoutHeight - 1 && (grid[i + 1][j] == '|' || grid[i + 1][j] == 'x'));
    bool canGoLeft = (j > 0 && (grid[i][j - 1] == '-' || grid[i][j - 1] == 'x'));
    bool canGoRight = (j < layoutWidth - 1 && (grid[i][j + 1] == '-' || grid[i][j + 1] == 'x'));

    // Randomly choose a new direction that the car can go
    std::vector<Direction> possibleDirections;
    possibleDirections.clear();
    if (canGoUp) {
        if(direction != down) possibleDirections.push_back(Direction::up);
    }
    if (canGoDown) {
        if (direction != up) possibleDirections.push_back(Direction::down);
    }
    if (canGoLeft) {
        if(direction != right) possibleDirections.push_back(Direction::left);
    }
    if (canGoRight) {
        if(direction != left) possibleDirections.push_back(Direction::right);
    }

    if(grid[i][j] == 'x') {
        if(direction == up){
            for(int i=0; i<4; i++){
                if(canGoLeft) possibleDirections.push_back(Direction::left);
                if(canGoRight) possibleDirections.push_back(Direction::right);
            }
        }
        else if(direction == down){
            for(int i=0; i<4; i++){
                if(canGoLeft) possibleDirections.push_back(Direction::left);
                if(canGoRight) possibleDirections.push_back(Direction::right);
            }
        }
        else if(direction == left){
            for(int i=0; i<4; i++){
                if(canGoUp) possibleDirections.push_back(Direction::up);
                if(canGoDown) possibleDirections.push_back(Direction::down);
            }
        }
        else if(direction == right){
            for(int i=0; i<4; i++){
                if(canGoUp) possibleDirections.push_back(Direction::up);
                if(canGoDown) possibleDirections.push_back(Direction::down);
            }
        }
    }

    if (!possibleDirections.empty()) {
        // Choose a random direction from the available directions
        int randomIndex = rand() % possibleDirections.size();
        Direction newDirection = possibleDirections[randomIndex];
        SetDirection(newDirection);
    }

        
    

}

