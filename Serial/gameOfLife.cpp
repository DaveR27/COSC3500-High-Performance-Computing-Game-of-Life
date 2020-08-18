#include <iostream>
#include <math.h>
#include "Vect2D.cpp"

using namespace std;

class Grid {
    public:
        int width, height;
        Vect2D grid;
        Vect2D neighborhood;
        int deadValue = 0;
        int aliveValue = 1;
        Grid(int width, int height) {
            width = width; // x-axis
            height = height; //y-axis
            grid = Vect2D(width, height);
            createNeighborhood();
        }
        void createNeighborhood();
        Vect2D getGrid();
        Vect2D getNeighbors();
        Vect2D aliveNeighbors();
        void evolve();
        Vect2D convolve(Vect2D, Vect2D);
};

void Grid::createNeighborhood() {
    neighborhood = Vect2D(3,3);
    neighborhood.insert(1,1,deadValue);
}


Vect2D Grid::getGrid() {
    return grid;
}

Vect2D Grid::getNeighbors() {
    return convolve(grid, neighborhood);
}

Vect2D Grid::aliveNeighbors() {
    return getNeighbors();
}



/*
Given the state of a cell the GoL rules apply:
- Any live call with fewer than 2 neighbors dies = underpopulation
- Any live cell with two or three live neighbors lives on to the next gen
- Any live cell with more than 3 live neighbors dies = overpopulation
- Any dead cell with exactly 3 live neighbors becomes living = reproduction
*/
void Grid::evolve() {
    Vect2D neighbors = aliveNeighbors();
    
    for (int i=0; i<width; i++) {
            for (int j=0; j<height; j++) {
                int element = int(neighbors.index(i,j));

                if (element < 2) {
                    grid.insert(i,j,deadValue);
                }
                if (element > 3) {
                    grid.insert(i,j,deadValue);
                }
                if (element == 3) {
                    grid.insert(i,j,aliveValue);
                }
            }
        }
}

// //convolve output will have the same size matrix as the biggest one given, ie the grid.
// Vect2D Grid::convolve(Vect2D grid, 
//     Vect2D neighborhood) {
        
// }

Vect2D Grid::convolve(Vect2D grid, Vect2D neighborhood)
{
    double sum;
    for(int y = 1; y < grid.getWidth() - 1; y++){
        for(int x = 1; x < grid.getHeight() - 1; x++){
            sum = 0;
            for(int k = -1; k <= 1;k++){
                for(int j = -1; j <=1; j++){
                    sum = sum + neighborhood.index(j+1, k+1)*grid.index(y - j, x - k);
                }
            }
            grid.insert(y, x, sum);
        }
    }
    return grid;
}

