//------------------------------------------------------------------------------
// Tree.cpp - provides implementation for the tree-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Tree.h"

// Gets the correctly interpreted vowel count proportion (for tree).
double tree::GetVowelProportion(void * const ptr) {
    return reinterpret_cast<Tree*>(ptr)->plant->vowel_count_proportion;
}

// Sets the data of a tree with file-typed values.
bool tree::Input(FILE * const file, void * const ptr) {
    Tree *new_ptr = reinterpret_cast<Tree*>(ptr);
    Input(file, new_ptr->plant);
    long long age;
    fscanf(file, "%lld", &age);
    new_ptr->age = fabs(age);
    return true;
}

// Sets the data of a tree with random-generated values.
bool tree::InputRnd(void *ptr) {
    Tree *new_ptr = reinterpret_cast<Tree*>(ptr);
    InputRnd(new_ptr->plant);
    new_ptr->age = rand() % 500 + 1;
    return true;
}

// Sets the C-string-type data of a given tree into a char**-pointer.
bool tree::ToString(const void * const ptr, char* *data) {
    const Tree *new_ptr = reinterpret_cast<const Tree*>(ptr);
    char *plant_data;
    ToString(new_ptr->plant, &plant_data);
    *data = new char[101];
    snprintf(*data, 100, "Tree %s:%lld years", plant_data, new_ptr->age);
    (*data)[100] = '\0';
    delete [] plant_data;
    return true;
}