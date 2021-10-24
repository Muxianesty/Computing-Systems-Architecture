//------------------------------------------------------------------------------
// Flower.cpp - provides implementation for the flower-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Flower.h"


// Default "flower"-object constructor.
Flower::Flower() : Plant() {
    this->flower_type_ = FlowerType::Domestic;
}

/* Special constructor, which has different ways of creating a
 * "flower"-object depending on what type of input was selected. */
Flower::Flower(bool from_file, FILE *file) : Plant(from_file, file) {
    if (from_file) {
        int flower_type;
        fscanf(file, "%d", &flower_type);
        flower_type = abs(flower_type);
        flower_type = ((flower_type > 3 || !flower_type) ? flower_type % 3 + 1 : flower_type);
        this->flower_type_ = static_cast<Flower::FlowerType>(flower_type);
    } else {
        this->flower_type_ = static_cast<Flower::FlowerType>(rand() % 3 + 1);
    }
}

// Sets the C-string-type data of a given flower into a char**-pointer.
char *Flower::toString() {
    char *plant_data = static_cast<Plant>(*this).toString();
    char *flower_type_data = getType();
    char *data = new char[101];
    data[100] = '\0';
    int print_count = snprintf(data, 100, "Flower %s:%s", plant_data, flower_type_data);
    data[print_count] = '\0';
    delete[] plant_data;
    delete[] flower_type_data;
    return data;
}

// Gets a C-string representation of a flower type.
char *Flower::getType() {
    char *data = new char[16];
    data[15] = '\0';
    int symbols_count;
    switch (this->flower_type_) {
        case Flower::FlowerType::Domestic:
            symbols_count = snprintf(data, 15, "Domestic");
            break;
        case Flower::FlowerType::Garden:
            symbols_count = snprintf(data, 15, "Garden");
            break;
        case Flower::FlowerType::Wild:
            symbols_count = snprintf(data, 15, "Wild");
            break;
    }
    data[symbols_count] = '\0';
    return data;
}