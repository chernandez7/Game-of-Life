/*Published under The MIT License (MIT)
See LICENSE*/

// Christopher Hernandez

#include <iostream>
#include <cstdlib>
#include <mpi.h>

#include "colony.h"
#include "my_timer.h"
#include "my_mpi_header.h"

Colony::Colony(int length, int width, int generations) {
  // 2 added for edges of grid
  this->length = length + 2;
  this->width = width + 2;
  this->currentGen = 0;
  this->maxGen = generations; // 100 default

  // dynamically initialize 2d array
  this->gen0 = new int*[this->length];
  this->currentGrid = new int*[this->length];
  this->times = new double*[this->length];

  // create columns
  for(int i = 0; i < this->length; i++) {
      this->gen0[i] = new int[this->width];
      this->currentGrid[i] = new int[this->width];
      this->times[i] = new double[this->width];
  }

  // random seed
  srand(time(NULL));

  // init values to 0
  for(int k = 0; k < this->length; k++) {
    for(int j = 0; j < this->width; j++) {
      gen0[k][j] = rand() % 2;;
      this->times[k][j] = 0;
    }
  }
  _copyGrid(gen0, currentGrid);
}

Colony::~Colony() {
  // free up memory
  for(int i = 0; i < this->length; ++i) {
    delete [] this->gen0[i];
    delete [] this->currentGrid[i];
    delete [] this->times[i];
  }
  delete [] this->gen0;
  delete [] this->currentGrid;
  delete [] this->times;
}

int* Colony::_partition_range (const int global_start, const int global_end,
                     const int num_partitions, const int rank);

void Colony::evolve() {
  int rank, size, local_start, local_end;
  callMPI( MPI_Comm_rank(MPI_COMM_WORLD, &rank) );
  callMPI( MPI_Comm_size(MPI_COMM_WORLD, &size) );

  // create rows
  int** temp = new int*[this->length];

  // create columns
  for(int k = 0; k < this->length; k++) {
      temp[k] = new int[this->width];
  }

  // move current data to a temp array
  _copyGrid(this->currentGrid, temp);

  int* range;
  /* create array to hold ranges
  // 0: amount of complete rows
  // 1: remainder of incomplete rows
  //
  // Ex. if n is 100 and size is 2
  // rank 0 gets 50, rank 1 gets 50
  */
  range = partition_range(0, this->length * this->width, size, rank);

  // range[0], width will get all complete rows
  for(int i = 1; i < range[0] - 1; i++) { // foreach cell
    for(int j = 1; j < this->width - 1; j++) {
      //start timing
      myTimer_t t0 = getTimeStamp();

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

       double t1 = getElapsedTime(t0, getTimeStamp()); // end gen time
       this->times[i][j] = t1;
    }
  }

  // Remainder line
  for (int l = 0; l < range[1] - 1; l++) {
    //start timing
    myTimer_t t0 = getTimeStamp();

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

    double t1 = getElapsedTime(t0, getTimeStamp()); // end gen time
    this->times[range[0]][l] = t1;
  }

  _copyGrid(temp, this->currentGrid); // move results back to original
  this->currentGen++; // increment generation
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
  std::cout << "Max Generations: " << this->maxGen - 1 << std::endl;
  std::cout << "Dimensions: " << this->length << "x" << this->width << std::endl;
}

double** Colony::getTimes() {
  return this->times;
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
    std::cout << "#";
  }
  std::cout << std::endl;
}

int* Colony::_partition_range(const int global_start, const int global_end,
                     const int num_partitions, const int rank) {
  int* temp = new int[2];

   // Total length of the iteration space.
   const int global_length = global_end - global_start;

   // Simple per-partition size ignoring remainder.
   const int chunk_size = global_length / num_partitions;

   // And now the remainder.
   const int remainder = global_length - chunk_size * num_partitions;

   // We want to spreader the remainder around evening to the 1st few ranks.
   // ... add one to the simple chunk size for all ranks < remainder.
   if (rank < remainder) {
      temp[0]   = global_start + rank * chunk_size + rank;
      temp[1]   = local_start + chunk_size + 1;
   } else {
      temp[0]   = global_start + rank * chunk_size + remainder;
      temp[1]   = local_start + chunk_size;
   }
   std::cout << "rank " << rank << ": " << temp[0] << " " << temp[1] << std::endl;
   return temp;
}
