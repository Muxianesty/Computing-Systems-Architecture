//------------------------------------------------------------------------------
// PlantContainer.h - provides declaration for the container of plants_-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Plant-entity classes/Flower.h"
#include "Plant-entity classes/Tree.h"
#include "Plant-entity classes/Bush.h"
#include "Plant-entity classes/Plant.h"

class PlantContainer {
    /* I remember about the optimal initialization
     * of the max size constant (via enumeration), yet
     * this time I decided to go with the classic
     * way to do so.*/
private:
    static const int kMax_size = 10000;
    int current_size_ = 0;
    int capacity_;
    Plant **plants_;
public:
    PlantContainer();

    explicit PlantContainer(int);

    ~PlantContainer();

    bool inputFromFileOrRnd(FILE *, bool);

    bool containerOutput(FILE *);

    int containerBinarySearch(double, int, int);

    void containerBinaryInsertionSort();
};



