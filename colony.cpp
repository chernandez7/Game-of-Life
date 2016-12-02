/*Published under The MIT License (MIT)
See LICENSE*/

// Christopher Hernandez

#include <iostream>
#include "colony.h"

Colony::Colony(int length, int width, int generations) {
  // 2 added for edges of grid
  this->length = length + 2;
  this->width = width + 2;
  this->currentGen = 0;
  this->maxGen = generations; // 100 default

  // dynamically initialize 2d array
  this->gen0 = new int*[this->length];
  this->currentGrid = new int*[this->length];

  // create columns
  for(int i = 0; i < this->length; i++) {
      this->gen0[i] = new int[this->width];
      this->currentGrid[i] = new int[this->width];
  }

  // random seed
  srand(time(NULL));

  // init values to 0
  for(int k = 0; k < this->length; k++) {
    for(int j = 0; j < this->width; j++) {
      gen0[k][j] = rand() % 2;;
      //currentGrid[k][j] = 0;
    }
  }
  _copyGrid(gen0, currentGrid);
}

Colony::~Colony() {
  // free up memory
  for(int i = 0; i < this->length; ++i) {
    delete [] this->gen0[i];
    delete [] this->currentGrid[i];
  }
  delete [] this->gen0;
  delete [] this->currentGrid;

}

void Colony::evolve() {
  int** temp = new int*[this->length];

  // create columns
  for(int k = 0; k < this->length; k++) {
      temp[k] = new int[this->width];
  }

  std::cout << "Temp initialized" << std::endl;

  _copyGrid(this->currentGrid, temp); // move current data to a temp array

  std::cout << "Copied current state into temp" << std::endl;

  for(int i = 1; i < this->length - 1; i++) { // foreach cell
    for(int j = 1; j < this->width - 1; j++) {
      // Using Moore's neighborhood model

      // 1 being that the cell is alive
      // 0 being that the cell is dead
      int count = 0; // cell's "value"

      // Locations relative to each cell
      count = temp[i-1][j] + // Left
					temp[i-1][j-1] + // Top Left
					temp[i][j-1] + // Top
					temp[i+1][j-1] + // Top Right
					temp[i+1][j] + // Right
					temp[i+1][j+1] + // Bottom Right
					temp[i][j+1] + // Bottom
					temp[i-1][j+1]; // Bottom Left

      if (count > 3 || count < 2) { // Overpopulation or Loneliness
         temp[i][j] = 0; // Cell dies
       }

       if (count == 2) { // Cell stays the same
         temp[i][j] = this->currentGrid[i][j];
       }

       if (count == 3) { // New cell is born
         temp[i][j] = 1;
       }
    }
  }
  _copyGrid(temp, this->currentGrid); // move results back to original
  std::cout << "Copied results to currentGrid" << std::endl;
  this->currentGen++;
}

void Colony::printGrid() {
  // top border
  _printSpacer(this->width);

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

  _printSpacer(this->width);
  std::cout << "Current Generation: " << this->currentGen << std::endl;
  std::cout << "Max Generations: " << this->maxGen << std::endl;
  std::cout << "Dimensions: " << this->length << "x" << this->width << std::endl;

}

int Colony::getMaxGens() {
  return this->maxGen;
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
        // init values to 0
        for(int k = 0; k < this->length; k++) {
          for(int j = 0; j < this->width; j++) {
            temp[k][j] = original[k][j];
          }
        }
  } else { // don't copy
    std::cerr << "2 Grids aren't the same size" << std::endl;
    return;
  }
}

void Colony::_printSpacer(int width) {
  for (int k = 0; k < this->width; k++) {
    std::cout << "-";
  }
  std::cout << std::endl;
}
