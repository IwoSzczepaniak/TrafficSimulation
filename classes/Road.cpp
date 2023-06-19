#include "Road.h"

Road::Road(SDL_Renderer* renderer, int x, int y, int width, int height)
    : renderer(renderer), x(x), y(y), width(width), height(height) {}

void Road::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect roadRect = { x, y, width, height };
    SDL_RenderFillRect(renderer, &roadRect);
}
