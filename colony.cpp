/*Published under The MIT License (MIT)
See LICENSE*/

// Christopher Hernandez

#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <math.h>

#include "colony.h"
#include "my_timer.h"
#include "my_mpi_header.h"

Colony::Colony(int length, int width, int generations) {
  // 2 added for edges of grid
  this->length = length + 2;
  this->width = width + 2;
  this->n = this->length * this->width;
  this->currentGen = 0;
  this->maxGen = generations; // 100 default

  // dynamically initialize 2d array
  this->gen0 = new int[this->n];
  this->currentGrid = new int[this->n];
  this->times = new double[this->n];

  // random seed
  srand(time(NULL));

  // init values to 0
  for(int i = 0; i < this->n; i++) {
      this->gen0[i] = rand() % 2;
      this->times[i] = 0;
  }
  this->currentGrid = this->gen0;
}

Colony::~Colony() {
  // free up memory
  delete [] this->gen0;
  delete [] this->currentGrid;
  delete [] this->times;
}

void Colony::evolve() {
  int rank, size, local_start, local_end;
  callMPI( MPI_Comm_rank(MPI_COMM_WORLD, &rank) );
  callMPI( MPI_Comm_size(MPI_COMM_WORLD, &size) );
  _partition_range(0, this->n, size, rank, local_start, local_end);
  // create rows
  int* temp = new int[this->n];
  temp = this->currentGrid;

  // range[0], width will get all complete rows
  for(int i = local_start; i < local_end; i++) { // foreach cell
    //start timing
    myTimer_t t0 = getTimeStamp();

    // Using Moore's neighborhood model
    // 1 being that the cell is alive
    // 0 being that the cell is dead
    int count = 0; // cell's "value"

    // Locations relative to each cell
    count = temp[i-1] +          // Left
    	temp[i-(1+this->width)] +  // Top Left
    	temp[i-(this->width)] +    // Top
    	temp[i-(this->width-1)] +  // Top Right
    	temp[i+1] +                // Right
    	temp[i+(1+this->width)] +  // Bottom Right
    	temp[i+(this->width)] +    // Bottom
    	temp[i+(this->width-1)];   // Bottom Left

    if (count > 3 || count < 2) { // Overpopulation or Loneliness
       temp[i] = 0; // Cell dies
     }

     if (count == 2) { // Cell stays the same
       temp[i] = this->currentGrid[i];
     }

     if (count == 3) { // New cell is born
       temp[i] = 1;
     }

     double t1 = getElapsedTime(t0, getTimeStamp()); // end gen time
     this->times[i] = t1;
   }

  this->currentGrid = temp; // move results back to original
  this->currentGen++; // increment generation
}

void Colony::printGrid() {
  int rank, size, local_start, local_end;
  callMPI( MPI_Comm_rank(MPI_COMM_WORLD, &rank) );
  callMPI( MPI_Comm_size(MPI_COMM_WORLD, &size) );
  _partition_range(0, this->n, size, rank, local_start, local_end);

  // top border
  _printSpacer(this->width);

  for(int j = 0; j < this->length; j++) { // ignore first and last lines
 		for(int i = 0; i < this->width; i++) {
			if(this->currentGrid[j*i] == 1) {
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
  std::cout << "MPI Rank: " << rank << "/" << size << std::endl;
  std::cout << "MPI Partition: " << local_start << "-" << local_end << std::endl;
}

double* Colony::getTimes() {
  return this->times;
}

void Colony::_printSpacer(int width) {
  for (int k = 0; k < this->width; k++) {
    std::cout << "#";
  }
  std::cout << std::endl;
}

void Colony::_partition_range(const int global_start, const int global_end,
  const int num_partitions, const int rank, int& local_start, int& local_end)
{
  // Total length of the iteration space.
  const int global_length = global_end - global_start;

  // Simple per-partition size ignoring remainder.
  const int chunk_size = global_length / num_partitions;

  // And now the remainder.
  const int remainder = global_length - chunk_size * num_partitions;

  // We want to spreader the remainder around evening to the 1st few ranks.
  // ... add one to the simple chunk size for all ranks < remainder.
  if (rank < remainder) {
     local_start = global_start + rank * chunk_size + rank;
     local_end   = local_start + chunk_size + 1;
  }
  else {
     local_start = global_start + rank * chunk_size + remainder;
     local_end   = local_start + chunk_size;
  }
}
