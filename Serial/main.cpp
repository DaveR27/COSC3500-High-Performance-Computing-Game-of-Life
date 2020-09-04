
#include "gameOfLife.cpp"
#include <fstream>
#include <string>
#include <time.h>
using namespace std;


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


int main(int argc, char const *argv[]) {
    // clock_t t1, t2;
    // t1 = clock(); //starts timer for experiments

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
    switch (argc) {
        case 6:
            grid.insertPatternFromFile(argv[1]);
            break;
        
        default:
            grid.insertGlider();
            break;
    }
    
    const string visStatus = "NoVis";
    //bool vis = false;
    if (visStatus.compare(visOut)) {
        VisLoop(loop, generations, width, height, grid);
        //vis = true;
    } else {
        grid.playGOL(loop, generations);
    }

    //End of experiments
    // t2 = clock();
    // float tickDiff ((float)t2-(float)t1);
    // float sec = tickDiff/CLOCKS_PER_SEC;
    // cout<<sec<<endl;
    // if (vis == false) {
    //     grid.outputGrid();
    // }
    return 0;
}