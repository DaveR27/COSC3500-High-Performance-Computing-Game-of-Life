#include <iostream>
#include <math.h>
#include "Vect2D.cpp"
#include <vector>

using namespace std;

class Grid {
    public:
        int width, height;
        Vect2D grid;
        Vect2D neighborhood;
        int deadValue = 0;
        int aliveValue = 1;
        Grid(int x, int y) {
            width = x; // x-axis
            height = y; //y-axis
            // cout<<width<<endl;
            // cout<<height<<endl;
            grid = Vect2D(x, y);
            // cout<<grid.colSize<<endl;
            // cout<<grid.rowSize<<endl;
            createNeighborhood();
        }

    void createNeighborhood() {
        neighborhood = Vect2D(3,3);
        neighborhood.insert(1,1,deadValue);
    }

    Vect2D getGrid() {
        return grid;
    }

    int aliveNeighbors(int i, int j) {
        int topL = 0; // neighbors[0]
        int topM = 0; // neighbors[1]
        int topR = 0; // neighbors[2]
        int middleL = 0; // neighbors[3]
        int middleR = 0; // neighbors[4]
        int bottomL = 0; // neighbors[5]
        int bottomM = 0; // neighbors[6]
        int bottomR = 0; // neighbors[7]

        int neighbors[8] = {topL, topM, topR, middleL, middleR, bottomL, bottomM, bottomR};
        int neighborsSize = 8;
        int aliveCells = 0;

        //Handling Boundries
        if (i != 0) {
            neighbors[0] = grid.index(i-1, j-1);
            neighbors[1] = grid.index(i-1, j);
            neighbors[2] = grid.index(i-1, j+1);
        } 

        if (j != 0) {
            neighbors[0] = grid.index(i-1, j-1);
            neighbors[3] = grid.index(i, j-1);
            neighbors[5] = grid.index(i+1, j-1);
        }

        if (i != height) {
            neighbors[5] = grid.index(i+1, j-1);
            neighbors[6] = grid.index(i+1, j);
            neighbors[7] = grid.index(i+1, j+1);
        }

        if (j != width) {
            neighbors[2] = grid.index(i-1, j+1);
            neighbors[4] = grid.index(i, j+1);
            neighbors[7] = grid.index(i+1, j+1);
        }

        for (int x=0; x<neighborsSize; x++) {
            if (neighbors[x] == 1) {
                aliveCells++;
            }
        }
        return aliveCells;
    }

    void updateGrid(vector<pair<int,int>> vect, int deadOrAlive) {
        for (uint i = 0; i < vect.size(); i ++) {
            grid.insert(vect[i].first, vect[i].second, deadOrAlive);
        }
    }

    /*
    Given the state of a cell the GoL rules apply:
    - Any live call with fewer than 2 neighbors dies = underpopulation
    - Any live cell with two or three live neighbors lives on to the next gen
    - Any live cell with more than 3 live neighbors dies = overpopulation
    - Any dead cell with exactly 3 live neighbors becomes living = reproduction
    */
    void evolve() {
        vector<pair<int,int>> killPos;
        vector<pair<int,int>> alivePos;

        for (int a=0; a<width; a++){
            for(int b=0; b<height; b++) {
                int aliveCells = aliveNeighbors(a, b);

                if (aliveCells < 2) {
                    killPos.push_back(make_pair(a, b));
                }
                if (aliveCells > 3) {
                    killPos.push_back(make_pair(a, b));
                }
                if (aliveCells == 3) {
                    alivePos.push_back(make_pair(a, b));
                }
            }
        }

        // for (int i=0; i<width; i++) {
        //     for (int j=0; j<height; j++) {
        //         int aliveCells = aliveNeighbors(i,j);
        //         cout<<"IN EVOLVE"<<endl;
        //         if (aliveCells < 2) {
        //             killPos.push_back(make_pair(i,j));
        //         }
        //         if (aliveCells > 3) {
        //             killPos.push_back(make_pair(i,j));
        //         }
        //         if (aliveCells == 3) {
        //             alivePos.push_back(make_pair(i,j));
        //         }
        //     }
        // }   

        
        updateGrid(killPos, deadValue);
        updateGrid(alivePos, aliveValue);

        // for(int k=0; k < 50; k ++) {
        //     for (int z=0; z < 50; z++){
        //         cout<<grid.index(k,z);
        //     }
        //     cout<<endl;
        // }
        // cout << '\n';  
        
    }



    void GoL(int moves) {
        int i = 0;
        while (i < moves) {
            evolve();
            i++;
        }
    }

    void insertGlider() {
        grid.insert(0,1, aliveValue);
        grid.insert(1,2, aliveValue);
        grid.insert(2,0, aliveValue);
        grid.insert(2,1, aliveValue);
        grid.insert(2,2, aliveValue);
    }

};


