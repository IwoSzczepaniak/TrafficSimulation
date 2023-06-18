#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "TrafficLight.h"
#include "Road.h"
#include "Car.h"

class Map {
private:
    std::vector<std::vector<char>> grid;
    int width;
    int height;
    SDL_Renderer* renderer;
    SDL_Renderer* carRenderer;
    std::vector<TrafficLight> trafficLights;
    std::vector<Road> roads;
    std::vector<Car> cars;
    bool state = false;

public:
    Map(const char** layout, int layoutWidth, int layoutHeight, SDL_Renderer* sdlRenderer);

    bool isCar(char cell){ return cell == '>' or cell == '<' or cell == '^' or cell == 'v';}

    void Init();

    void Render();

    void changeLights();
};
