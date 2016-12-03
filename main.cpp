/*Published under The MIT License (MIT)
See LICENSE*/

// Christopher Hernandez

#include <iostream>
#include <cstdlib>
#include "colony.h"

int _length;
int _width;
int _gens;

double calculateAvgTime(double** times) {
  double total = 0;

  for(int j = 0; j < _length; j++) {
 		for(int i = 0; i < _width; i++) {
      total += times[j][i]; // add up all times
    }
  }
  return total / (_length * _width); // sum / n = avg
}

int main(int argc, char** argv) {
  _length = atoi(argv[1]);
  _width = atoi(argv[2]);
  _gens = atoi(argv[3]);
  // Create colony
  Colony c(_length, _width, _gens);

  for (int i = 0; i < _gens; i++) {
    system("clear"); // clear console
    c.printGrid();
    c.evolve();
    system("sleep .1"); // give console time to catch up
}
  std::cout << "Average timestep: " << calculateAvgTime(c.getTimes()) << std::endl;
  return 0;
}
