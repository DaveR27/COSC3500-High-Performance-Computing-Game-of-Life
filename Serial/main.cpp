
#include "gameOfLife.cpp"

using namespace std;


int main() {
    int width = 5;
    int height = 5;
    Grid grid(width, height);

    

    for (int i=0; i < width; i++) {
        for (int j=0; j < height; j++) {
            cout << grid.grid[i][j] << " ";
        }
        cout << endl;
    }
};