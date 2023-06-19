FILES = classes/Road.cpp classes/TrafficLight.cpp classes/Car.cpp classes/Map.cpp
OUTPUT = traffic_simulator
GCC = g++
CPPFLAGS = -Wall -g -std=c++11  -lSDL2 -lSDL2_image

all:
	$(GCC) main.cpp $(FILES) -o $(OUTPUT) $(CPPFLAGS)
test:
	./$(OUTPUT)
clean:
	rm $(OUTPUT)