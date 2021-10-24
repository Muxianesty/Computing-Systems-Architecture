//------------------------------------------------------------------------------
// Plant.h - provides declaration for the plant-struct
// and functions working with it.
//------------------------------------------------------------------------------
#pragma once

#include "string.h"
#include "math.h"
#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"


class Plant {
protected:
    char *name_ = nullptr;
    int name_length_ = 0;
    double vowel_count_proportion_ = 0;

    void countVowelProportion();

public:
    double getProportion() const;

    Plant();

    // I had to use a ref('&') in order to define a copying constructor.
    Plant(const Plant &);

    Plant(bool, FILE *);

    ~Plant();

    void output(FILE *);

    virtual char *toString();
};

bool isAVowel(const char *);

char *randomName(int);
