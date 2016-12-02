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

    // Constructors
    Colony(int length, int width);
    Colony(int length, int width, int generations);
    // Destructor
    ~Colony();
    // Checks surrounding cells and determines if cell dies
    void evolve(int** grid);
    // Prints grid of cells
    void printGrid();
};

#endif
