#include <iostream>
#include <math.h>
#include "Vect2D.cu"
#include <vector>
#include <fstream>
#include <omp.h>

using namespace std;

class Grid {
    public:
        int width, height;
        Vect2D grid;
        
        Grid(int x, int y) {
            width = x; // x-axis
            height = y; //y-axis
            grid = Vect2D(x, y);
        }

    /*
    Returns the current state of the grid
    */
    Vect2D getGrid() {
        return grid;
    }



    /*
    Automatically places out a simulation on the grid.

    @param int loop: initial starting point.
    @param int generations: how long the generations will last
    */
    void playGOL(int loop, int generations){
        while (loop <= generations) {
            evolve();
            loop++; 
        }
    }

    /*
    Writes the current state of the grid to a file.
    */
    void outputGrid(){
        ofstream file;
        file.open("game_of_life_save.txt");
        for (int i=0; i < width; i++) {
            for (int j=0; j < height; j++) {
                file << grid.index(i, j);
            } 
            file << endl;
        }
        file << endl;
           
        file.close();
    }




};


