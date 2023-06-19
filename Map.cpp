#include <iostream>
#include "Map.h"
#include "common.h"

#include <stdio.h>
#include <thread>


Map::Map(const char** layout,  int layoutWidth, int layoutHeight, SDL_Renderer* sdlRenderer, int carAmount) {
    this->layoutWidth = layoutWidth;
    this->layoutHeight = layoutHeight;
    this->renderer = sdlRenderer;
    this->carAmount = carAmount;
    
    grid.resize(layoutHeight, std::vector<char>(layoutWidth));
    for (int i = 0; i < layoutHeight; i++) {
        for (int j = 0; j < layoutWidth; j++) {
            grid[i][j] = layout[i][j];
        }
    }
}

Map::~Map(){
    for (auto car:cars) delete car;
    for (auto road:roads) delete road;
    for (auto trafficLight:trafficLights) delete trafficLight;
}

void Map::CreateCar(SDL_Rect rect, int speed){
    Car *car = new Car(renderer, rect.x, rect.y, rect.w, rect.h, speed, layoutWidth, layoutHeight);
    cars.push_back(car);
}

void Map::CreateRoad(SDL_Rect rect){
    Road *road = new Road(renderer, rect.x, rect.y, rect.w, rect.h);
    roads.push_back(road);
}

bool IsTrafficLight(char cell){
    return cell == '*' or cell == ':';
}

void Map::CreateTrafficLight(char cell, SDL_Rect rect){
    TrafficLight* trafficLight = new TrafficLight(renderer, rect.x, rect.y, rect.h);
    if (cell == '*') {
        trafficLight->SetState(TrafficLight::TrafficLightState::Green);
    } else if (cell == ':') {
        trafficLight->SetState(TrafficLight::TrafficLightState::Red);
    }
    trafficLights.push_back(trafficLight);
}

void Map::changeLights(){
    for (int i = 0; i < trafficLights.size(); i++) {
        trafficLights[i]->changeLights();
    }
    state++;
    state %= 2;
}

void Map::Init(int carSpeed)
{
    cellWidth = WINDOW_WIDTH/layoutWidth ;
    cellHeight = WINDOW_HEIGHT/layoutHeight;
    srand(time(NULL));

    for (int i = 0; i < layoutHeight; i++) {
        for (int j = 0; j < layoutWidth; j++) {
            SDL_Rect rect;
            rect.x = j * cellWidth;
            rect.y = i * cellHeight;
            rect.w = cellWidth;
            rect.h = cellHeight;
            char cell = grid[i][j];

            if (cell == '|' or cell == '-' or cell == 'x') {
                CreateRoad(rect);
            } 
            else if (IsTrafficLight(cell)) {
                CreateTrafficLight(cell, rect);   
            } 
            else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            SDL_RenderFillRect(renderer, &rect);
        }
    }

    while(carAmount>0)
    {
        int x = rand() % layoutWidth;
        int y = rand() % layoutHeight;
        char cell = grid[y][x];
        if (IsRoad(cell)) {
            SDL_Rect rect;
            rect.x = x * cellWidth;
            rect.y = y * cellHeight;
            rect.w = cellWidth;
            rect.h = cellHeight;
            CreateCar(rect, carSpeed);
            carAmount--;
        }
    }
}

void Map::Render() {
    for (int i = 0; i < trafficLights.size(); i++) {
        trafficLights[i]->Render();
    }
    for (int i = 0; i < roads.size(); i++) {
        roads[i]->Render();
    }
    
    for (int i = 0; i < cars.size(); i++) {
        cars[i]->Render();
        cars[i]->Move(state);
        

        int xi = cars[i]->GetX();
        int yi = cars[i]->GetY();

        int grid_i = yi/cellHeight;
        int grid_j = xi/cellWidth;

        bool canGoUp = (grid_i > 0 && (grid[grid_i - 1][grid_j] == '|' || grid[grid_i - 1][grid_j] == 'x'));
        bool canGoDown = (grid_i < layoutHeight - 1 && (grid[grid_i + 1][grid_j] == '|' || grid[grid_i + 1][grid_j] == 'x'));
        bool canGoLeft = (grid_j > 0 && (grid[grid_i][grid_j - 1] == '-' || grid[grid_i][grid_j - 1] == 'x'));
        bool canGoRight = (grid_j < layoutWidth - 1 && (grid[grid_i][grid_j + 1] == '-' || grid[grid_i][grid_j + 1] == 'x'));

        bool isX = (grid[grid_i][grid_j] == 'x');


        cars[i]->DecideDirection(canGoUp, canGoDown, canGoLeft, canGoRight, isX);
    }
}


