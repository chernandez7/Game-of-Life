#include <iostream>
#include "colony.h"

Colony::Colony(int length, int width) {
  // 2 added for edges of grid
  this->length = length + 2;
  this->width = width + 2;  

  std::cout << "Colony created with dimensions " << length << "x" << width  << std::endl;
}
