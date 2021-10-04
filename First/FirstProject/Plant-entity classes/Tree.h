//------------------------------------------------------------------------------
// Tree.h - provides declaration for the tree-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Plant.h"

namespace tree {
    struct Tree {
        /* Due to "long" values range
         * depending on the architecture
         * of the OS, it was decided
         * to use "long long"-type. */
    public: plant::Plant * plant = nullptr;
    public: long long int age;
    };

    double GetVowelProportion(void * const);
    bool Input(FILE * const, void * const);
    bool InputRnd(void *);
    bool ToString(const void * const, char**);
}

