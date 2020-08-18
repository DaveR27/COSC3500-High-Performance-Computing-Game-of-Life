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
            array = std::vector<double>(size, 0);
        }
        Vect2D() {
            rowSize = 250;
            colSize = 250;
            size = rowSize*colSize;
            array = std::vector<double>(size, 0);
        }
        double index(int, int);
        int getsize();
        int getWidth();
        int getHeight();
        void insert(int, int, double);
};

double Vect2D::index(int row, int col) {
    return array[(row*col) + col];
}

void Vect2D::insert(int row, int col, double Ele) {
    array[(row*col) + col] = Ele;
}

int Vect2D::getWidth() {
    return rowSize;
}

int Vect2D::getHeight() {
    return colSize;
}

int Vect2D::getsize() {
    return size;
}