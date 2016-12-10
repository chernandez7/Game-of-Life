/*Published under The MIT License (MIT)
See LICENSE*/

// Christopher Hernandez

#ifndef COLONY_H
#define COLONY_H

class Colony {
  private:
    // get length of grid
    int _getLength(int** grid);
    // get width of grid
    int _getWidth(int** grid);
    // Copies values of original grid into a temporary grid
    void _copyGrid(int** original, int** temp);
    // Prints horizontal spacer
    void _printSpacer(int width);
    int* _partition_range(const int global_start, const int global_end,
                          const int num_partitions, const int rank);
  public:
    // Dimensions of grid
    int length;
    int width;

    // amount of generations
    int currentGen;
    int maxGen;

    // initial generation
    int** gen0;
    // grid of current state
    int** currentGrid;

    // times for each gen
    double** times;

    // Constructor
    Colony(int length, int width, int generations);
    // Destructor
    ~Colony();
    // Checks surrounding cells and determines if cell dies
    void evolve();
    // Prints grid of cells
    void printGrid();
    // Get times of get
    double** getTimes();
};

#endif
