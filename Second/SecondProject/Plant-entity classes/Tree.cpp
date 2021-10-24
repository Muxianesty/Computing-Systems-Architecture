//------------------------------------------------------------------------------
// Tree.cpp - provides implementation for the tree-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Tree.h"

// Default "tree"-object constructor.
Tree::Tree() : Plant(){
    this->age_ = 0;
}

/* Special constructor, which has different ways of creating a
 * "tree"-object depending on what type of input was selected. */
Tree::Tree(bool from_file, FILE *file) : Plant(from_file, file) {
    if (from_file) {
        fscanf(file, "%lld", &this->age_);
        this->age_ = abs(this->age_);
    } else {
        this->age_ = rand() % 500 + 1;
    }
}

// Sets the C-string-type data of a given tree into a char**-pointer.
char *Tree::toString() {
    char *plant_data = static_cast<Plant>(*this).toString();
    char *data = new char[101];
    data[100] = '\0';
    int print_count = snprintf(data, 100, "Tree %s:%lld years", plant_data, this->age_);
    data[print_count] = '\0';
    delete [] plant_data;
    return data;
}