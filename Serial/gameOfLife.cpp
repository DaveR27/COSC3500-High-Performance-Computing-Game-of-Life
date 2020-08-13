#include <vector>
#include <iostream>

using namespace std;

class Grid {
    public:
        int width, height;
        vector<vector<int>> grid;
        vector<vector<int>> neighborhood;
        Grid(int width, int height) {
            width = width;
            height = height;
            grid = vector<vector<int>>(width, vector<int>(height, 0));
            createNeighborhood();
        }
        void createNeighborhood();
        void aliveNeighbors();
        void getNeighbors();
        void evolve();
};

void Grid::createNeighborhood() {
    neighborhood = vector<vector<int>>(3,
        vector<int>(3,1));
    neighborhood[1][1] = 0;
}

void Grid::getNeighbors() {
    
}



/*
Given the state of a cell the GoL rules apply:
- Any live call with fewer than 2 neighbors dies = underpopulation
- Any live cell with two or three live neighbors lives on to the next gen
- Any live cell with more than 3 live neighbors dies = overpopulation
- Any dead cell with exactly 3 live neighbors becomes living = reproduction
*/
void Grid::evolve() {

}


