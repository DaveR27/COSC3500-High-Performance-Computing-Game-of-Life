#include <vector>

class Vect2D {
    private:
        int rowSize, colSize, size;
        

    public:
        std::vector<int> array;
        Vect2D(int x, int y) {
            rowSize = x;
            colSize = y;
            size = rowSize*colSize;
            array = std::vector<int>(size, 0);
        }
        Vect2D() {
            rowSize = 250;
            colSize = 250;
            size = rowSize*colSize;
            array = std::vector<int>(size, 0);
        }
        
        int index(int row, int col) {
            return array[(row * colSize) + col];
        }

        void insert(int row, int col, double Ele) {
            array[(row * colSize) + col] = Ele;
        }

        int getWidth() {
            return rowSize;
        }

        int getHeight() {
            return colSize;
        }

        int getsize() {
            return size;
        }
};
