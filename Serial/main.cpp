
#include "gameOfLife.cpp"
#include<fstream>

int main(int argc, char const *argv[]) {
    int moves;
    int width;
    int height;
    int loop = 1;
    ofstream file;
    file.open("game_of_life_save.txt");

    if (argc == 5) {
        //argv[1] is the file you want to insert
        width = atoi(argv[2]); //argv[2]
        height = atoi(argv[3]); //argv[3]
        moves = atoi(argv[4]); //argv[4]
        
    } else {
        //argv[1] is the file you want to insert
        width = 256; //argv[2]
        height = 256; //argv[3]
        moves = 50; //argv[4]
        
    }

    //Grid that life is simulated on
    Grid grid(width, height);
    switch (argc) {
        case 5:
            grid.insertPatternFromFile(argv[1]);
            break;
        
        default:
            grid.insertGlider();
            break;
    }
    
    //Loop to write out to file from c
    while (loop <= moves) {

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