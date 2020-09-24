#include <iostream>
#include <math.h>
#include "Vect2D.cpp"
#include <vector>
#include <fstream>
#include <omp.h>

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
            grid = Vect2D(x, y);
        }

    /*
    Returns the current state of the grid
    */
    Vect2D getGrid() {
        return grid;
    }

    /*
    Checks to see if what cells are alive directly around a given index.

    @param int i: first index.
    @param int j: second index.
    */
    int aliveNeighbors(int h, int w) {
        int aNeighbors = 0;
        for (int k=-1; k <= 1; k++) {
            for (int l=-1; l <= 1; l++) {
                if (!(k == 0 && l == 0)) {
                    
                    int neigh = grid.index(k + h, l + w);
                    if ((neigh == aliveValue)) {
                        aNeighbors++;
                    }
                    
                }
            }
        }
        
        return aNeighbors;
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

    After these rules have been checked, the grid is then updated.
    */
    void evolve() {
        vector<pair<int,int>> killPos;
        vector<pair<int,int>> alivePos;
        int a, b;
        #pragma omp parallel for private(b) collapse(2)
        for (a=0; a<width; a++){
            for(b=0; b<height; b++) {
                
                // int aliveCells = aliveNeighbors(a, b);
                

                // if (aliveCells < 2) {
                //     killPos.push_back(make_pair(a, b));
                    
                // }
                // if (aliveCells > 3) {
                //     killPos.push_back(make_pair(a, b));
                    
                // }
                // if (aliveCells == 3) {
                //     alivePos.push_back(make_pair(a, b));
                    
                // }
            }
        }

        //updateGrid(killPos, deadValue);
        
        //updateGrid(alivePos, aliveValue);
        
        
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


    /*
    Takes a txt file and inserts the pattern into the middle fo the grid

    @param string fileName: String that is the path to a .txt pattern file
    */
    void insertPatternFromFile(string fileName) {
        ifstream file(fileName);
        string line;
        int centering = 0;
        bool centered = false;
        int i = 0;
        while(getline(file, line)) {
            if(centered == false){
                centering += line.size();
                centered = true;
            }
            for (uint j=0; j<line.length(); j++) {
                if (line[j] == 'O') {
                    grid.insert((i+(width/2)) - (centering/2), (j+(height/2)) - (centering/2), aliveValue);
                }
            }
            i++;
        }
    }

};


