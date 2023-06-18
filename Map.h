#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "TrafficLight.h"
#include "Road.h"
#include "Car.h"

class Map {
private:
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<char>> carGrid;
    int width;
    int height;
    SDL_Renderer* renderer;
    std::vector<TrafficLight> trafficLights;
    std::vector<Road> roads;
    std::vector<Car> cars;
    bool state = false;

public:
    Map(const char** layout, const char** layoutWithCars, int layoutWidth, int layoutHeight, SDL_Renderer* sdlRenderer);

    bool isCar(char cell){ return cell == '>' or cell == '<' or cell == '^' or cell == 'v';}

    void Init();

    void Render();

    void changeLights();
};
