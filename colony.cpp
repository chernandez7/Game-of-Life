/*Published under The MIT License (MIT)
See LICENSE*/

// Christopher Hernandez

#include <iostream>
#include "colony.h"

Colony::Colony(int length, int width) {
  // 2 added for edges of grid
  this->length = length + 2;
  this->width = width + 2;

  // dynamically initialize 2d array
  this->gen0 = new int*[this->length];
  this->currentGrid = new int*[this->length];

  // create columns
  for(int i = 0; i < this->length; i++) {
      this->gen0[i] = new int[this->width];
      this->currentGrid[i] = new int[this->width];
  }
  std::cout << "Dynamic allocation worked" << std::endl;
  // init values to 0
  for(int k = 0; k < this->length; k++) {
    for(int j = 0; j < this->width; j++) {
      gen0[k][j] = 1;
      currentGrid[k][j] = 1;
    }
  }
  std::cout << "init worked" << std::endl;

  //_copyGrid(gen0, this->gen0);
  //std::cout << "copy1 worked" << std::endl;

  //_copyGrid(this->gen0, this->currentGrid); // current grid at init is gen0
  //std::cout << "copy2 worked" << std::endl;

  std::cout << "Colony created with dimensions " << length << "x" << width  << std::endl;
}

Colony::~Colony() {
  /*free up memory
  for(int i = 0; i < this->length; ++i) {
    delete [] this->gen0[i];
    delete [] this->currentGrid[i];
  }
  delete [] this->gen0;
  delete [] this->currentGrid;
  */
}

void Colony::life(int** grid) {}

void Colony::printGrid() {
  for(int j = 0; j < this->length; j++) { // ignore first and last lines
 		for(int i = 0; i < this->width; i++) {
			if(this->currentGrid[j][i] == 1) {
				std::cout << '*'; // alive
      } else {
				std::cout << ' '; // dead
      }
    }
		std::cout << std::endl;
 	}
}

int Colony::_getLength(int** grid) {
  // total size / one row
  return (sizeof grid / sizeof grid[0]);
}

int Colony::_getWidth(int** grid) {
  // row size / int
  return (sizeof grid[0] / sizeof(int));
}

void Colony::_copyGrid(int** original, int** temp) {
  if (_getLength(original) == _getLength(temp) &&
      _getWidth(original) == _getWidth(temp)) { // check that both have same dimensions
        std::cout << "both grids share dimensions" << std::endl;
    for(int j = 0; j < _getLength(original); j++) { // iterated through every j and i
  		for(int i = 0; i < _getWidth(original); i++)
  			temp[j][i] = original[j][i];
  	}
  } else { // don't copy
    std::cerr << "2 Grids aren't the same size" << std::endl;
    return;
  }
}
