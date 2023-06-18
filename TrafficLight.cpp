#include "TrafficLight.h"
#include <SDL2/SDL_image.h>

// TO DO
TrafficLight::TrafficLight(SDL_Renderer* renderer, int x, int y, int size)
    : renderer(renderer), x(x), y(y), size(size/2), state(TrafficLightState::Red) {
    redTexture = LoadTexture("resources/red.png");
    greenTexture = LoadTexture("resources/green.png");
}

void TrafficLight::SetState(TrafficLightState newState) {
    state = newState;
}



TrafficLight::TrafficLightState TrafficLight::GetState() {
    return state;
}

void TrafficLight::Render() {
    SDL_Texture* texture = (state == TrafficLightState::Red) ? redTexture : greenTexture;

    SDL_Rect destRect = { x, y, size, size };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

SDL_Texture* TrafficLight::LoadTexture(const char* filename) {
    SDL_Surface* surface = IMG_Load(filename);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

int TrafficLight::GetX() {
    return x;
}

int TrafficLight::GetY() {
    return y;
}