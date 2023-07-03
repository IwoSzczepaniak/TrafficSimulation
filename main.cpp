#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>

#include "classes/Road.h"
#include "classes/TrafficLight.h"
#include "classes/Car.h"
#include "classes/Map.h"

const char** layout;
Map* map;

std::vector<std::string> readLayout(const char* mapFile){
    std::ifstream file(mapFile);
    if (!file) {
        std::cerr << "Failed to open map file: " << mapFile << std::endl;
        exit(1);
    }
    std::vector<std::string> layoutLines;
    std::string line;
    while (std::getline(file, line)) {
        layoutLines.push_back(line);
    }
    file.close();

    layout = new const char*[layoutLines.size()];
    for (size_t i = 0; i < layoutLines.size(); ++i) {
        layout[i] = layoutLines[i].c_str();
    }
    return layoutLines;
}

void createMap(SDL_Window* window,SDL_Renderer* renderer, const char* mapFile, int carAmount, int carSpeed){

    std::vector<std::string> layoutLines = readLayout(mapFile);

    int layoutWidth = strlen(layout[0]);
    int layoutHeight = layoutLines.size();

    map = new Map(layout, layoutWidth, layoutHeight, renderer, carAmount);
    map->Init(carSpeed);

}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Traffic Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    const char* mapFile = "resources/map.txt";
    int carAmount = 50;
    int carSpeed = 1;

    createMap(window, renderer, mapFile, carAmount, carSpeed);

    // Main loop
    bool running = true;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 elapsedTime = 0;
    Uint32 lightChangeInterval = 2000;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        elapsedTime += currentTime - lastTime;
        lastTime = currentTime;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if (elapsedTime >= lightChangeInterval) {
            elapsedTime = 0;
            map->changeLights();
        }

        map->Render();

        SDL_RenderPresent(renderer);
        usleep(500);
    }

    // Cleanup and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // Cleanup dynamically allocated memory
    delete[] layout;
    delete map;

    return 0;
}
