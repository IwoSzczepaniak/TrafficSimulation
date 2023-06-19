#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "Road.h"
#include "TrafficLight.h"
#include "Car.h"
#include "Map.h"


int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create a window and renderer
    SDL_Window* window = SDL_CreateWindow("Traffic Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    const char* layout[] = {
        ".......*...*........",
        ".x-------x--------x.",
        ".||------|-------||.",
        ".||.....:|:......||.",
        ".||......|.......||.",
        ".||..*..:|:..*...||.",
        ".|x------|-------||.",
        ".x-------x--------x.",
        ".|x------|-------||.",
        ".||..*..:|:..*...||.",
        ".||......|.......||.",
        ".||.....:|:......||.",
        ".|x------|-------|x.",
        ".x-------x--------x.",
        ".......*...*........"
    };
    int carAmount = 25;


    int layoutWidth = strlen(layout[0]);
    int layoutHeight = sizeof(layout) / sizeof(layout[0]);

    // Create a map
    Map map(layout, layoutWidth, layoutHeight, renderer, carAmount);

    map.Init();


    // Main loop
    bool running = true;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 elapsedTime = 0;
    Uint32 lightChangeInterval = 2000;  // Change the light every 2 seconds


    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Update the simulation
        Uint32 currentTime = SDL_GetTicks();
        elapsedTime += currentTime - lastTime;
        lastTime = currentTime;

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if (elapsedTime >= lightChangeInterval) {
            elapsedTime = 0;
            map.changeLights();
        }

        // Render the map
        map.Render();

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
