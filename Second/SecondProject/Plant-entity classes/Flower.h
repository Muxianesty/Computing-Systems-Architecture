//------------------------------------------------------------------------------
// Flower.h - provides declaration for the flower-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Plant.h"

class Flower : public Plant {
    enum FlowerType {
        Domestic = 1, Garden, Wild
    };
private:
    FlowerType flower_type_;

public:
    Flower();
    Flower(bool, FILE *);
    char *toString() override;
    char *getType();
};


