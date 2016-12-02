/*Published under The MIT License (MIT)
See LICENSE*/

// Christopher Hernandez

#include <iostream>
#include "colony.h"

int main(int argc, char** argv) {
  Colony c(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

  for (int i = 0; i < c.getMaxGens(); i++) {
    system("clear");
    c.printGrid();
    c.evolve();
    system("sleep .1");
}

  return 0;
}
