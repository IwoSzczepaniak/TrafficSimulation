#include <SDL2/SDL.h>

#include "Road.h"
#include "TrafficLight.h"
#include "Car.h"
#include "Map.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create a window and renderer
    SDL_Window* window = SDL_CreateWindow("Traffic Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // // Create a road instance
    Road road(renderer, 100, 200, 600, 100);

    // // Create a traffic light instance
    TrafficLight trafficLight(renderer, 380, 150, 40);

    // Create car instances
    Car car1(renderer, 100, 220, 40, 20, 2);
    Car car2(renderer, 200, 260, 40, 20, 1);

    // Map map(renderer, 100, 200, 600, 100);

    // char* layout[] = {
    //     "----|---",
    //     "...:|*..",
    //     "....|...",
    //     "....|...",
    //     "...*|...",
    //     "----|---",
    //     "...:....."
    // };

    // int layoutWidth = strlen(layout[0]);
    // int layoutHeight = sizeof(layout) / sizeof(layout[0]);

    // Map map(renderer, 100, 200, layoutWidth * 20, layoutHeight * 20, layout);



    // Main loop
    bool running = true;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 elapsedTime = 0;
    Uint32 lightChangeInterval = 1000;  // Change the light every 5 seconds

    while (running) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Update the simulation
        Uint32 currentTime = SDL_GetTicks();
        elapsedTime += currentTime - lastTime;
        lastTime = currentTime;

        if (elapsedTime >= lightChangeInterval) {
            elapsedTime = 0;
            TrafficLight::TrafficLightState newState = (trafficLight.GetState() == TrafficLight::TrafficLightState::Red) ? TrafficLight::TrafficLightState::Green : TrafficLight::TrafficLightState::Red;
            trafficLight.SetState(newState);
        }

        car1.Update(trafficLight);
        car2.Update(trafficLight);

        // Render the road, traffic light, and cars
        road.Render();
        trafficLight.Render();
        car1.Render();
        car2.Render();

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
