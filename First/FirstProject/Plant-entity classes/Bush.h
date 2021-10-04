//------------------------------------------------------------------------------
// Bush.h - provides declaration for the bush-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Plant.h"
#include "stdio.h"

namespace bush {
    struct Bush {
        enum BlossomMonth {
            January = 1, February, March, April, May, June,
            July, August, September, October, November, December };
    public: plant::Plant *plant = nullptr;
    public: BlossomMonth month;
    };

    double GetVowelProportion(void * const);
    bool Input(FILE * const, void * const);
    bool InputRnd(void * const);
    bool ToString(const void * const, char**);

    bool GetMonth(const Bush * const, char**);
}
