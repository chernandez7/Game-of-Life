/*Published under The MIT License (MIT)
See LICENSE*/

// Christopher Hernandez

#include <iostream>
#include <cstdlib>
#include "colony.h"

int main(int argc, char** argv) {
  Colony c(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

  for (int i = 0; i < c.getMaxGens(); i++) {
    system("clear"); // clear console
    c.printGrid();
    c.evolve();
    system("sleep .1"); // give console time to catch up
}

  return 0;
}
