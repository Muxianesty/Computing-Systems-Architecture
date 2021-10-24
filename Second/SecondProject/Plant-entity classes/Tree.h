//------------------------------------------------------------------------------
// Tree.h - provides declaration for the tree-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Plant.h"


class Tree : public Plant {
    /* Due to "long" values range
     * depending on the architecture
     * of the OS, it was decided
     * to use "long long"-type. */
private:
    long long int age_;
public:
    Tree();
    Tree(bool, FILE *);
    char *toString() override;
};

