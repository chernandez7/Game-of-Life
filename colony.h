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
    // initial generation
    int** gen0;
    // grid of current state
    int** currentGrid;

    // Constructor
    Colony(int length, int width);
    // Destructor
    ~Colony();
    // Checks surrounding cells and determines if cell dies
    void life(int** grid);
    // Prints grid of cells
    void printGrid();
};

#endif
