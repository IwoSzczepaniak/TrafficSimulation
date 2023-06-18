#include <iostream>
#include "Map.h"
#include "common.h"

#include <stdio.h>


Map::Map(const char** layout, int layoutWidth, int layoutHeight, SDL_Renderer* sdlRenderer) {
    width = layoutWidth;
    height = layoutHeight;
    renderer = sdlRenderer;

    grid.resize(height, std::vector<char>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = layout[i][j];
        }
    }
}

Car setCarDir(SDL_Renderer* renderer, char cell, SDL_Rect rect, int i, int j){
    Car car = Car(renderer, rect.x, rect.y, rect.w, rect.h, 1, i, j);
    switch (cell)
    {
    case '>':
        car.SetSpeed(rand() % 1 + 1);
        car.SetDirection(Car::Direction::right);
        break;
    case '<':
        car.SetSpeed((-1)*(rand() % 1 + 1));
        car.SetDirection(Car::Direction::left);
        break;
    case '^':
        car.SetDirection(Car::Direction::up);
        car.SetSpeed(rand() % 1 + 1);
        break;
    case 'v':
        car.SetDirection(Car::Direction::down);
        car.SetSpeed((-1)*(rand() % 1 + 1));
        break;
    default:
        break;
    }
    return car;
}

void createCar(SDL_Renderer* renderer, char cell, SDL_Rect rect, std::vector<Car>& cars, int i, int j){
    Car car = setCarDir(renderer, cell, rect, i, j);
    cars.push_back(car);
}

void createRoad(SDL_Renderer* renderer, SDL_Rect rect, std::vector<Road>& roads){
    Road road = Road(renderer, rect.x, rect.y, rect.w, rect.h);
    roads.push_back(road);
}

bool isTrafficLight(char cell){
    return cell == '*' or cell == ':';
}

void createTrafficLight(SDL_Renderer* renderer, char cell, SDL_Rect rect, std::vector<TrafficLight>& trafficLights){
    TrafficLight trafficLight = TrafficLight(renderer, rect.x, rect.y, rect.h);
    if (cell == '*') {
        trafficLight.SetState(TrafficLight::TrafficLightState::Green);
    } else if (cell == ':') {
        trafficLight.SetState(TrafficLight::TrafficLightState::Red);
    }
    trafficLights.push_back(trafficLight);
}

void Map::Init() {
    int cellWidth = WINDOW_WIDTH/width ;
    int cellHeight = WINDOW_HEIGHT/height;
    srand(time(NULL));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            SDL_Rect rect;
            rect.x = j * cellWidth;
            rect.y = i * cellHeight;
            rect.w = cellWidth;
            rect.h = cellHeight;
            char cell = grid[i][j];

            if (cell == '|' or cell == '-' or cell == 'x') {
                createRoad(renderer, rect, roads);
            } 
            else if (isCar(cell)) {
                createCar(renderer, cell, rect, cars, i, j);
                createRoad(renderer, rect, roads);
            }            
            else if (isTrafficLight(cell)) {
                createTrafficLight(renderer, cell, rect, trafficLights);   
            } 
            else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            SDL_RenderFillRect(renderer, &rect);
        }
    }
    
}


void Map::Render() {
    for (int i = 0; i < trafficLights.size(); i++) {
        trafficLights[i].Render();
    }
    for (int i = 0; i < roads.size(); i++) {
        roads[i].Render();
    }
    for (int i = 0; i < cars.size(); i++) {
        int grid_i = cars[i].GetX()/WINDOW_HEIGHT;
        int grid_j = cars[i].GetY()/WINDOW_WIDTH;
        if (grid[grid_i][grid_j] == 'x') {
            cars[i].onCrossroad(grid_i, height, grid_j, width);
        }
        cars[i].Update(this->state);
        cars[i].Render();
    }
}

void Map::changeLights(){
    for (int i = 0; i < trafficLights.size(); i++) {
        if (trafficLights[i].GetState() == TrafficLight::TrafficLightState::Green) {
            trafficLights[i].SetState(TrafficLight::TrafficLightState::Red);
            this->state = false;
        } else if (trafficLights[i].GetState() == TrafficLight::TrafficLightState::Red) {
            trafficLights[i].SetState(TrafficLight::TrafficLightState::Green);
            this->state = true;
        }
    }
}


