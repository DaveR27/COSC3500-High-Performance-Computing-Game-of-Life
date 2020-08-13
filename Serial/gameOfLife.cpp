#include <vector>
#include <iostream>

using namespace std;

class Grid {
    public:
        int width, height;
        vector<vector<int>> grid;
        Grid(int width, int height) {
            width = width;
            height = height;
            grid = vector<vector<int>>(width, vector<int>(height, 0));
        }
};


