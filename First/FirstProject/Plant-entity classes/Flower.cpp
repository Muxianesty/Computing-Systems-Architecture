//------------------------------------------------------------------------------
// Flower.cpp - provides implementation for the flower-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Flower.h"

// Gets the correctly interpreted vowel count proportion (for flower).
double flower::GetVowelProportion(void * const ptr) {
    return reinterpret_cast<Flower*>(ptr)->plant->vowel_count_proportion;
}

// Sets the data of a flower with file-typed values.
bool flower::Input(FILE * const file, void * const ptr) {
    Flower* new_ptr = reinterpret_cast<Flower*>(ptr);
    Input(file, new_ptr->plant);
    int flower_type;
    fscanf(file, "%d", &flower_type);
    flower_type = abs(flower_type);
    flower_type = ((flower_type > 3 || !flower_type) ? flower_type % 3 + 1 : flower_type);
    new_ptr->flower_type = static_cast<Flower::FlowerType>(flower_type);
    return true;
}

// Sets the data of a flower with random-generated values.
bool flower::InputRnd(void * const ptr) {
    Flower *new_ptr = reinterpret_cast<Flower*>(ptr);
    InputRnd(new_ptr->plant);
    new_ptr->flower_type = static_cast<Flower::FlowerType>(rand() % 3 + 1);
    return true;
}

// Sets the C-string-type data of a given flower into a char**-pointer.
bool flower::ToString(const void * const ptr, char* *data) {
    const Flower *new_ptr = reinterpret_cast<const Flower*>(ptr);
    char *plant_data;
    ToString(new_ptr->plant, &plant_data);
    char *flower_type_data = new char[16];
    GetType(new_ptr, &flower_type_data);
    *data = new char[101];
    snprintf(*data,100, "Flower %s:%s", plant_data, flower_type_data);
    (*data)[100] = '\0';
    delete [] plant_data;
    delete [] flower_type_data;
    return true;
}

// Gets a C-string representation of a flower type.
bool flower::GetType(const Flower * const flower, char* *data) {
    //*data = new char[16];
    int symbols_count;
    switch(flower->flower_type) {
        case Flower::FlowerType::Domestic: symbols_count = snprintf(*data,15, "Domestic"); break;
        case Flower::FlowerType::Garden: symbols_count = snprintf(*data,15, "Garden"); break;
        case Flower::FlowerType::Wild: symbols_count = snprintf(*data, 15, "Wild"); break;
    }
    (*data)[symbols_count] = '\0';
    return true;
}