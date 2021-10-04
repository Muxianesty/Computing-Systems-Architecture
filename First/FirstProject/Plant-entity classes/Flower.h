//------------------------------------------------------------------------------
// Flower.h - provides declaration for the flower-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Plant.h"

namespace flower {
    struct Flower {
        enum FlowerType {
            Domestic = 1, Garden, Wild
        };
    public: plant::Plant * plant = nullptr;
    public: FlowerType flower_type;
    };

    double GetVowelProportion(void * const);
    bool Input(FILE * const, void * const);
    bool InputRnd(void * const);
    bool ToString(const void * const, char**);

    bool GetType(const Flower * const, char**);
}


