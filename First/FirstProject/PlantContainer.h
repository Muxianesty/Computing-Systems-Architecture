//------------------------------------------------------------------------------
// PlantContainer.h - provides declaration for the container of plants-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Plant-entity classes/Flower.h"
#include "Plant-entity classes/Tree.h"
#include "Plant-entity classes/Bush.h"
#include "Plant-entity classes/Plant.h"
using namespace plant;
using namespace tree;
using namespace bush;
using namespace flower;

struct PlantContainer {
    /* I remember about the optimal initialization
     * of the max size constant (via enumeration), yet
     * this time I decided to go with the classic
     * way to do so.*/
public: const int max_size = 10000;
public: int current_size = 0;
public: int capacity;
public: void* *plants;
};

void InitializeContainer(PlantContainer*, int);
bool InputFromFileOrRnd(FILE * const, PlantContainer * const, bool);
bool Output(FILE * const, void * const);
bool ContainerOutput(FILE *const, const PlantContainer * const);
void CLearAndDelete(PlantContainer*);

int ContainerBinarySearch(PlantContainer * const, double, int, int);
void ContainerBinaryInsertionSort(PlantContainer *const);