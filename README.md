# 2D Traffic Simulation
This project is a simple 2D traffic simulation implemented in C++ using the SDL2 library. It simulates a basic traffic scenario where vehicles move on a road network and follow traffic lights.

### Prerequisites
Before running the simulation, ensure that you have the following dependencies installed on your system(tested on Ubuntu 22.04):

- C++ compiler
- SDL2 library

The project utilizes the SDL2 library for graphics rendering. Visit the SDL website for more information on SDL2.


## Usage
To run the traffic simulation, execute make and make test in terminal.

You can create your own road network by editing the layout in main.cpp file:
- "|" : Horizontal road
- "-" : Vertical road
- "." : Empty space
- "x" : Crossroad field
- ":" : Traffic light for north-south direction
- "*" : Traffic light for east-west direction

Cars are spawned randomly on the road network. You can change the amount by editing the carAmount variable in main.cpp file.
It is also possible to adjust the traffic lights' delay by changing the lightChangeInterval variable in main.cpp file and speed of the cars by changing the speed variable in car.cpp file.