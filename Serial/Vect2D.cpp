#include <vector>

class Vect2D {
    private:
        int rowSize;
        int colSize;
        int size;
        std::vector<double> array;

    public:
        Vect2D(int rowSize, int colSize) {
            rowSize = rowSize;
            colSize = colSize;
            size = rowSize*colSize;
            array = std::vector<double>(size, NULL);
        }
        double index(int, int);
        int size();
};

double Vect2D::index(int row, int col) {
    return array[(row*col) + col];
}