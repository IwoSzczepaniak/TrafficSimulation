#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "TrafficLight.h"
#include "Road.h"
#include "Car.h"

class Map {
private:
    std::vector<std::vector<char>> grid;
    int layoutWidth, layoutHeight, carAmount;
    int cellWidth, cellHeight;
    SDL_Renderer* renderer;
    SDL_Renderer* carRenderer;
    std::vector<TrafficLight*> trafficLights;
    std::vector<Road*> roads;
    std::vector<Car*> cars;
    int mapState = 1;

public:
    Map(const char** layout,  int layoutWidth, int layoutHeight, SDL_Renderer* sdlRenderer, int carAmount);

    bool IsCar(char cell){ return cell == '>' or cell == '<' or cell == '^' or cell == 'v';}

    bool IsRoad(char cell){ return cell == '|' or cell == '-' or cell == 'x';}

    void CreateCar(SDL_Rect rect, int speed);

    void CreateRoad(SDL_Rect rect);

    void CreateTrafficLight(char cell, SDL_Rect rect);

    void Init(int carSpeed);

    void Render();

    void changeLights();

    ~Map();
};
