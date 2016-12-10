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

int partition_range (const int global_start, const int global_end,
                     const int num_partitions, const int rank,
                     int& local_start, int& local_end) {
   // Total length of the iteration space.
   const int global_length = global_end - global_start;

   // Simple per-partition size ignoring remainder.
   const int chunk_size = global_length / num_partitions;

   // And now the remainder.
   const int remainder = global_length - chunk_size * num_partitions;

   // We want to spreader the remainder around evening to the 1st few ranks.
   // ... add one to the simple chunk size for all ranks < remainder.
   if (rank < remainder)
   {
      local_start = global_start + rank * chunk_size + rank;
      local_end   = local_start + chunk_size + 1;
   }
   else
   {
      local_start = global_start + rank * chunk_size + remainder;
      local_end   = local_start + chunk_size;
   }

   return 0;
}


int main(int argc, char** argv) {
  callMPI( MPI_Init(&argc, &argv) );

  int rank, size;
  callMPI( MPI_Comm_rank(MPI_COMM_WORLD, &rank) );
  callMPI( MPI_Comm_size(MPI_COMM_WORLD, &size) );

  //int local_start, local_end;
  //callMPI( partition_range(0, n, size, rank, local_start, local_end) );

  myTimer_t t0 = getTimeStamp();

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

  double t1 =  getElapsedTime(t0, getTimeStamp()); // end time
  std::cout << "Average timestep: " << calculateAvgTime(c.getTimes()) << " ms" << std::endl;
  std::cout << "Total Time: " << t1 << " ms" << std::endl;

  callMPI( MPI_Finalize() );
  return 0;
}
