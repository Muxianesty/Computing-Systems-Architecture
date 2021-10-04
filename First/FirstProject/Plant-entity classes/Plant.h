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

namespace plant {

    struct Plant {
        struct PseudoVTable {
        public: double (*GetVowelProportion)(void * const);
        public: bool (*Input)(FILE * const, void * const);
        public: bool (*InputRnd)(void *);
        public: bool (*ToString)(const void * const, char**);
        };
    public: PseudoVTable *vtable;
    public: char *name;
    public: int name_length;
    public: double vowel_count_proportion;
    };
    bool Input(FILE * const, Plant * const);
    bool InputRnd(Plant * const);
    bool ToString(const Plant * const, char**);

    double CountVowelProportion(Plant * const);
    bool IsAVowel(const char *);
    bool ClearSpace(Plant *);
    bool RandomName(int, char**);
}
