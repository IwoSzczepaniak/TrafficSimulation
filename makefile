all:
	g++ main.cpp Road.cpp TrafficLight.cpp Car.cpp -o traffic_simulator -lSDL2 -lSDL2_image
	./traffic_simulator