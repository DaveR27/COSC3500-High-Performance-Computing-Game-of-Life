#include <iostream>
#include <math.h>
#include "Vect2D.cpp"

using namespace std;

class Grid {
    public:
        int width, height;
        Vect2D grid;
        vector<vector<int>> neighborhood;
        int deadValue = 0;
        int aliveValue = 1;
        Grid(int width, int height) {
            width = width; // x-axis
            height = height; //y-axis
            grid = Vect2D(width, height);
            createNeighborhood();
        }
        void createNeighborhood();
        vector<vector<int>> getStates();
        vector<vector<int>> getGrid();
        vector<vector<int>> getNeighbors();
        vector<vector<int>> aliveNeighbors();
        void evolve();
        vector<vector<int>> convolve(vector<vector<int>>,
            vector<vector<int>>);
        private:
            int convertFtoI(float);
};

void Grid::createNeighborhood() {
    neighborhood = vector<vector<int>>(3,
        vector<int>(3,1));
    neighborhood[1][1] = 0;
}

vector<vector<int>> Grid::getStates() {
    return grid;
}

vector<vector<int>> Grid::getGrid() {
    return getStates();
}

vector<vector<int>> Grid::getNeighbors() {
    return convolve(grid, neighborhood);
}

vector<vector<int>> Grid::aliveNeighbors() {
    return getNeighbors();
}

int convertFtoI(float x) {
    if (x >= 0) {
        return (int) (x + 0.5);
    } else {
        return (int) (x - 0.5);
    }
}


/*
Given the state of a cell the GoL rules apply:
- Any live call with fewer than 2 neighbors dies = underpopulation
- Any live cell with two or three live neighbors lives on to the next gen
- Any live cell with more than 3 live neighbors dies = overpopulation
- Any dead cell with exactly 3 live neighbors becomes living = reproduction
*/
void Grid::evolve() {
    vector<vector<int>> neighbors = aliveNeighbors();
    
    for (int i=0; i<width; i++) {
            for (int j=0; j<height; j++) {
                int element = convertFtoI(round(neighbors[i][j]));

                if (element < 2) {
                    grid[i][j] = deadValue;
                }
                if (element > 3) {
                    grid[i][j] = deadValue;
                }
                if (element == 3) {
                    grid[i][j] = aliveValue;
                }
            }
        }
}

//convolve output will have the same size matrix as the biggest one given, ie the grid.
vector<vector<int>> Grid::convolve(vector<vector<int>> grid, 
    vector<vector<int>> neighborhood) {
        
}

