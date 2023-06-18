all:
	g++ main.cpp Road.cpp TrafficLight.cpp Car.cpp Map.cpp -o traffic_simulator -lSDL2 -lSDL2_image
	./traffic_simulator
clean:
	rm traffic_simulator