#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <SDL2/SDL.h>

class TrafficLight {
public:
    enum class TrafficLightState { Red, Green };

    TrafficLight(SDL_Renderer* renderer, int x, int y, int size);
    void SetState(TrafficLightState newState);
    TrafficLightState GetState();
    void Render();
    int GetX();
    int GetY();
    void changeLights();

private:
    SDL_Renderer* renderer;
    int x, y, size;
    TrafficLightState state;
    SDL_Texture* redTexture;
    SDL_Texture* greenTexture;

    SDL_Texture* LoadTexture(const char* filename);
};

#endif
