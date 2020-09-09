
#include "gameOfLife.cpp"
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

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

//Runs Program
int main(int argc, char const *argv[]) {
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
    Grid grid(width, height);
    grid.insertPatternFromFile(argv[1]);
        
    
    const string visStatus = "NoVis";
    if (visStatus.compare(visOut)) {
        VisLoop(loop, generations, width, height, grid); //For visualizing
    } else {
        grid.playGOL(loop, generations); //For just running simulation
    }

   
    return 0;
}