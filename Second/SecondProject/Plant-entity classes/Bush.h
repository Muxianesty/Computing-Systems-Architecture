//------------------------------------------------------------------------------
// Bush.h - provides declaration for the bush-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Plant.h"
#include "stdio.h"

class Bush : public Plant {
    enum BlossomMonth {
        January = 1, February, March, April, May, June,
        July, August, September, October, November, December
    };
private:
    BlossomMonth month_;

public:
    Bush();
    Bush(bool, FILE *);
    char *toString() override;
    char *getMonth();
};




