#include "Car.h"
#include "TrafficLight.h"

Car::Car(SDL_Renderer* renderer, int x, int y, int width, int height, int speed)
    : renderer(renderer), x(x), y(y), width(width), height(height), speed(speed), roadWidth(600) {}

void Car::Update(TrafficLight trafficLight) {
    if (trafficLight.GetState() == TrafficLight::TrafficLightState::Green or x > trafficLight.GetX() - width or x < trafficLight.GetX() - width) {
        x += speed;
        if (x > roadWidth) {
            x = -width;  // Wrap around to the start of the road
        }
    }
}

void Car::Render() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_Rect carRect = { x, y, width, height };
    SDL_RenderFillRect(renderer, &carRect);
}

