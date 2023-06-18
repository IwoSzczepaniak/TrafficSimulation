
#include <vector>

class Map {
public:
    Map(SDL_Renderer* renderer, int x, int y, int width, int height, char** layout) :
        renderer(renderer), x(x), y(y), width(width), height(height) {
        // Initialize the map elements
        CreateElements(layout);
    }

    void RenderMap() {
        // Render the road elements
        for (auto& road : roads) {
            road.Render();
        }

        // Render the traffic light elements
        for (auto& trafficLight : trafficLights) {
            trafficLight.Render();
        }
    }

    // Getters for roads and traffic lights

private:
    SDL_Renderer* renderer;
    int x, y, width, height;
    std::vector<Road> roads;
    std::vector<TrafficLight> trafficLights;

    void CreateElements(char** layout) {
        // Create roads and traffic lights based on the layout

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (layout[i][j] == '-') {
                    // Create a horizontal road
                    Road road(renderer, x + j * 20, y + i * 20, 20, 20);
                    roads.push_back(road);
                } else if (layout[i][j] == '|') {
                    // Create a vertical road
                    Road road(renderer, x + j * 20, y + i * 20, 20, 20);
                    roads.push_back(road);
                } else if (layout[i][j] == '*' || layout[i][j] == ':') {
                    // Create a traffic light
                    TrafficLight trafficLight(renderer, x + j * 20, y + i * 20, 20);
                    trafficLights.push_back(trafficLight);

                    if (layout[i][j] == '*') {
                        trafficLight.SetState(TrafficLight::TrafficLightState::Green);
                    } else if (layout[i][j] == ':') {
                        trafficLight.SetState(TrafficLight::TrafficLightState::Red);
                    }
                }
            }
        }
    }
};
