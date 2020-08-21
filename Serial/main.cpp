
#include "gameOfLife.cpp"
#include<fstream>

int main() {
    ofstream file;
    file.open("game_of_life_save.txt");
    int width = 50;
    int height = 50;
    Grid grid(width, height);
    int loop = 0;
    int moves = 4;
    
    grid.insertGlider();

    // for (int i=0; i < width; i++) {
    //         for (int j=0; j < height; j++) {
    //             cout <<grid.grid.index(i, j);
    //         }
    //         cout << endl;
    // }
    
    // cout << endl;
    // cout<<grid.grid.index(0,1)<<endl;
    // cout<<grid.grid.index(1,2)<<endl;
    // cout<<grid.grid.index(2,0)<<endl;
    // cout<<grid.grid.index(2,1)<<endl;
    // cout<<grid.grid.index(2,2)<<endl;

    // grid.grid.insert(0,1,0);
    // grid.grid.insert(1,2, 0);
    // grid.grid.insert(2,0, 0);
    // grid.grid.insert(2,1, 0);
    // grid.grid.insert(2,2, 0);

    // cout<<grid.grid.index(0,1)<<endl;
    // cout<<grid.grid.index(1,2)<<endl;
    // cout<<grid.grid.index(2,0)<<endl;
    // cout<<grid.grid.index(2,1)<<endl;
    // cout<<grid.grid.index(2,2)<<endl;



    //grid.GoL(moves);

    // for (int i=0; i < width; i++) {
    //         for (int j=0; j < height; j++) {
    //             cout <<grid.grid.index(i, j);
    //         }
    //         cout << endl;
    // }
    
    // cout << endl;



    
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