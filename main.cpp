/*Published under The MIT License (MIT)
See LICENSE*/

// Christopher Hernandez

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h> 
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
  clock_t begin = clock();

  _length = atoi(argv[1]);
  _width = atoi(argv[2]);
  _gens = atoi(argv[3]);
  bool print = true;
  if (argv[4]) { // if 4th parameter exists don't print
    if (strncmp(argv[4],"--no-print", 10) == 0) {
      print = false;
    }
  }
  // Create colony
  Colony c(_length, _width, _gens);

  for (int i = 0; i < _gens; i++) {
    if (print) {
      system("clear"); // clear console
      c.printGrid();
      c.evolve();
      system("sleep .1"); // give console time to catch up
    } else {
      c.evolve();
    }
  }

  clock_t end = clock(); // end gen time
  double elapsed = double(end - begin) /  CLOCKS_PER_SEC;
  std::cout << "Average timestep: " << calculateAvgTime(c.getTimes()) << std::endl;
  std::cout << "Total Time: " << elapsed << std::endl;
  return 0;
}
