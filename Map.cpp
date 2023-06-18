#include <iostream>
#include "Map.h"

Map::Map(const char** layout, int layoutWidth, int layoutHeight, SDL_Renderer* sdlRenderer) {
    width = layoutWidth;
    height = layoutHeight;
    renderer = sdlRenderer;

    // Initialize the grid with the layout
    grid.resize(height, std::vector<char>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = layout[i][j];
        }
    }
}



void Map::Init() {
    int cellWidth = 800/width ;
    int cellHeight = 600/height;
    srand(time(NULL));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            SDL_Rect rect;
            rect.x = j * cellWidth;
            rect.y = i * cellHeight;
            rect.w = cellWidth;
            rect.h = cellHeight;
            char cell = grid[i][j];

            if (cell == '|') {
                Road road = Road(renderer, rect.x, rect.y, rect.w, rect.h);
                roads.push_back(road);
            } else if (cell == '-') {
                Road road = Road(renderer, rect.x, rect.y, rect.w, rect.h);
                roads.push_back(road);
            } else if (cell == 'x') {
                Road road = Road(renderer, rect.x, rect.y, rect.w, rect.h);
                roads.push_back(road);
            } else if (isCar(cell)) {

                Car car = Car(renderer, rect.x, rect.y, rect.w, rect.h, 1);
                car.SetOnCrossroad(false);
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
                cars.push_back(car);
                Road road = Road(renderer, rect.x, rect.y, rect.w, rect.h);
                roads.push_back(road);
            }

            
            
            else if (cell == '*' or cell == ':') {
                TrafficLight trafficLight = TrafficLight(renderer, rect.x, rect.y, rect.h);
                if (cell == '*') {
                    trafficLight.SetState(TrafficLight::TrafficLightState::Green);
                } else if (cell == ':') {
                    trafficLight.SetState(TrafficLight::TrafficLightState::Red);
                }
                trafficLights.push_back(trafficLight);
                
            } else if (cell == '.') {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }

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
        cars[i].Update(state);
        cars[i].Render();
    }
}

void Map::changeLights(){
    for (int i = 0; i < trafficLights.size(); i++) {
        if (trafficLights[i].GetState() == TrafficLight::TrafficLightState::Green) {
            trafficLights[i].SetState(TrafficLight::TrafficLightState::Red);
            state = false;
        } else if (trafficLights[i].GetState() == TrafficLight::TrafficLightState::Red) {
            trafficLights[i].SetState(TrafficLight::TrafficLightState::Green);
            state = true;
        }
    }
}

bool Map::onCrossroad(int x, int y){
    if(grid[y][x] == 'x') return true;
    return false;
}
