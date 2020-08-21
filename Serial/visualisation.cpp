#include "matplotlibcpp.h"
using namespace plt;

class Visual {
    public:
        long fig;
        void img;
        int interval = 200 //ms
        Grid* life;
        Vect2D cells;
        void Visual(Grid* grid) {
            fig = plt::figure();
            cells = *life.getGrid();
            img = plt::imshow(cells, true);
            ani = animation.FuncAnimation(fig, animate, 24, interval,
                true);
        }
        void animate();   
}

void Visual::animate() {
    *life.evolve();
    Vect2D cellsUpdated = *life.getStates();

    img.set_array(cellsUpdated);
    return img;
}

