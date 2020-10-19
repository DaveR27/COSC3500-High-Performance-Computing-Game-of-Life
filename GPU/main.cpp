
#include "gameOfLife.cpp"
#include <fstream>
#include <string>
#include <chrono> 
using namespace std;

const int deadValue = 0;
const int aliveValue = 1;

/*
Loop used to create a file of the generations used to visualise the running of a GoL pattern.

@param int loop: The starting generation.
@param int generations: The amount of generations the simulation will run for.
@param int width: The width of the grid that the world will reside in.
@param int height: The height of the grid that the world will reside in.
@param Grid grid: The grid that the simulation occurs on.
*/
void VisLoop(int loop, int generations, 
            int width, int height, Grid grid){
    ofstream file;
    file.open("game_of_life_save.txt");
    //Loop to write out to file from c
    while (loop <= generations) {

        for (int i=0; i < width; i++) {
            for (int j=0; j < height; j++) {
                file << grid.grid.index(i, j);
            }
            
            file << endl;
        }
        file << endl;

        grid.evolve();
        loop++;
    
    }   
    file.close();

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

/*
Given the state of a cell the GoL rules apply:
- Any live call with fewer than 2 neighbors dies = underpopulation
- Any live cell with two or three live neighbors lives on to the next gen
- Any live cell with more than 3 live neighbors dies = overpopulation
- Any dead cell with exactly 3 live neighbors becomes living = reproduction

After these rules have been checked, the grid is then updated.
*/
void evolve() {
    Vect2D temp = grid;
    int a, b;

    for (a=0; a<width; a++){
        for(b=0; b<height; b++) {
            
            int aliveCells = aliveNeighbors(a, b);
            
            if (aliveCells < 2 || aliveCells > 3) {
                temp.insert(a,b,deadValue);
                
            } else if (aliveCells == 3) {
                temp.insert(a,b,aliveValue);
            } 
        }
    }
    grid = temp;  
}



//Changes the mod operator to work like python
int modFix(int x, int dimension) {
    if (x < 0) {
        return dimension + (x % dimension);
    } else {
        return x % dimension;
    }
}

/*
Takes a txt file and inserts the pattern into the middle fo the grid

@param string fileName: String that is the path to a .txt pattern file
*/
void insertPatternFromFile(string fileName, int* (*grid)[], int width, int height) {
    
}

//Runs Program
int main(int argc, char const *argv[]) {
    auto start = chrono::high_resolution_clock::now();
    int generations;
    int width;
    int height;
    int loop = 1;
    string visOut = "NoVis";

    if (argc == 6) {
        //argv[1] is the file you want to insert
        width = atoi(argv[2]); //argv[2]
        height = atoi(argv[3]); //argv[3]
        generations = atoi(argv[4]); //argv[4]
        visOut = argv[5];
    } else {
        //argv[1] is the file you want to insert
        width = 256; //argv[2]
        height = 256; //argv[3]
        generations = 50; //argv[4]
        
    }
    
    //Grid that life is simulated on
    int grid[width][height];

    //Add pattern to the grid
    ifstream file(argv[1]);
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
                grid[modFix((i+(width/2)) - (centering/2), width)][modFix(j+(height/2) - (centering/2), height)] = aliveValue;
            }
        }
        i++;
    }

    



































    
    
    
    // const string visStatus = "NoVis";
    // if (visStatus.compare(visOut)) {
    //     VisLoop(loop, generations, width, height, grid); //For visualizing
    // } else {
    //     grid.playGOL(loop, generations); //For just running simulation
    // }

    // auto stop = chrono::high_resolution_clock::now();
    // auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
    // cout<<duration<<endl;
   
    return 0;
}