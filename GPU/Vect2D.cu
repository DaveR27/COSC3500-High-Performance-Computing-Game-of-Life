#include <vector>

class Vect2D {
    private:
        int rowSize, colSize, size; //Dimensions of the grid
        

    public:
        std::vector<int> array;
        Vect2D(int x, int y) {
            rowSize = x;
            colSize = y;
            size = rowSize*colSize;
            array = std::vector<int>(size, 0);
        }
        Vect2D() {
            rowSize = 256;
            colSize = 256;
            size = rowSize*colSize;
            array = std::vector<int>(size, 0);
        }

        
        
        /*
        Indexes into the vector and returns what is in that current index.

        @param int row: row that is being indexed.
        @param int col: the column that is being indexed.
        */
        int index(int row, int col) {
            return array[(modFix(row) * colSize) + modFix(col)];
        }

        /*
        Inserts a number into the vector at a given position.

        @param int row: row that is being indexed.
        @param int col: the column that is being indexed.
        @param double Ele: 
        */
        void insert(int row, int col, double Ele) {
            array[(modFix(row) * colSize) + modFix(col)] = Ele;
        }

        /*
        Gets the length of the rows for the grid.
        */
        int getWidth() {
            return rowSize;
        }
        
        /*
        Gets the length of the height for the grid.
        */
        int getHeight() {
            return colSize;
        }

        /*
        Gets the size of the grid.
        */
        int getsize() {
            return size;
        }
};
