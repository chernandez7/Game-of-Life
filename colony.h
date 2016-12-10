/*Published under The MIT License (MIT)
See LICENSE*/

// Christopher Hernandez

#ifndef COLONY_H
#define COLONY_H

class Colony {
  private:
    // Prints horizontal spacer
    void _printSpacer(int width);
    // Defines partition of a node
    int _partition_range(int global_start, int global_end, int num_partitions,
      int rank, int& local_start, int& local_end);
  public:
    // Dimensions of grid
    int length;
    int width;
    int n;

    // amount of generations
    int currentGen;
    int maxGen;

    // initial generation
    int* gen0;
    // grid of current state
    int* currentGrid;

    // times for each gen
    double* times;

    // Constructor
    Colony(int length, int width, int generations);
    // Destructor
    ~Colony();
    // Checks surrounding cells and determines if cell dies
    void evolve();
    // Prints grid of cells
    void printGrid();
    // Get times of get
    double* getTimes();
};

#endif
