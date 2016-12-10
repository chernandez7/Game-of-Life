/*Published under The MIT License (MIT)
See LICENSE*/

// Christopher Hernandez

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <mpi.h>

#include "colony.h"
#include "my_timer.h"
#include "my_mpi_header.h"

int _length;
int _width;
int _n;
int _gens;

double calculateAvgTime(double* times) {
  double total = 0;
 	for(int i = 0; i < _n; i++)
    total += times[i]; // add up all times

  return total / _n; // sum / n = avg
}

int main(int argc, char** argv) {
  // Init MPI
  callMPI( MPI_Init(&argc, &argv) );

  myTimer_t t0 = getTimeStamp();

  _length = atoi(argv[1]);
  _width = atoi(argv[2]);
  _n = _length * _width;
  _gens = atoi(argv[3]);
  bool print = true;
  if (argv[4]) { // if 4th parameter exists don't print
    if (strncmp(argv[4],"--no-print", 10) == 0) {
      print = false;
    }
  }

  // Defining Node's Rank and Size
  int rank, size;
  callMPI( MPI_Comm_rank(MPI_COMM_WORLD, &rank) );
  callMPI( MPI_Comm_size(MPI_COMM_WORLD, &size) );

  // Create colony
  Colony c(_length, _width, _gens);

  for (int i = 0; i < _gens; i++) {
    if (print) {
      if (rank == 0) { // only 1 output
        system("clear");
	c.printGrid();
      }
      c.evolve();
    } else {
      c.evolve();
    }
  }

  double t1 =  getElapsedTime(t0, getTimeStamp()); // end time
  if (rank == 0) {
    std::cout << "Average timestep: " << calculateAvgTime(c.getTimes()) << " ms" << std::endl;
    std::cout << "Total Time: " << t1 << " s" << std::endl;
  }
  // End MPI
  callMPI( MPI_Finalize() );
  return 0;
}
