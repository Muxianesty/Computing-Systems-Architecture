//------------------------------------------------------------------------------
// PlantContainer.cpp - provides implementation for the container of plants-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "PlantContainer.h"

// Initializes container with the given capacity.
void InitializeContainer(PlantContainer* container, int capacity) {
    if (capacity < 0 || capacity > container->max_size) {
        printf("!!Value %d is less than 0 or higher than 10000 and cannot be used as!!\n", capacity);
        printf("!!as container capacity - value '0' will be used instead!!");
        capacity = 0;
    }
    container->plants = new void*[capacity];
    container->capacity = capacity;
    container->current_size = 0;
}

// Fills the container depending on the flag (with random values or from file).
bool InputFromFileOrRnd(FILE * const file, PlantContainer * const cont, bool random) {
    for(int index = 0; index < cont->capacity && (random || !feof(file)); ++index, ++(cont->current_size)) {
        int rnd_type_id;
        // Deducing a given type given by the selected way of input.
        if (random) {
            rnd_type_id = rand() % 3 + 1;
        } else {
            fscanf(file, "%d", &rnd_type_id);
            rnd_type_id = abs(rnd_type_id);
            rnd_type_id = ((rnd_type_id > 3 || !rnd_type_id) ? rnd_type_id % 3 + 1 : rnd_type_id);
        }
        if (rnd_type_id == 1) {
            bush::Bush *bush = new bush::Bush;
            bush->plant = new plant::Plant;
            bush->plant->vtable = new plant::Plant::PseudoVTable;
            bush->plant->vtable->GetVowelProportion = bush::GetVowelProportion;
            bush->plant->vtable->Input = bush::Input;
            bush->plant->vtable->InputRnd = bush::InputRnd;
            bush->plant->vtable->ToString = bush::ToString;
            if (random) {
                bush->plant->vtable->InputRnd(bush);
            } else {
                bush->plant->vtable->Input(file,bush);
            }
            cont->plants[index] = bush;
        } else if (rnd_type_id == 2) {
            flower::Flower *flower = new flower::Flower;
            flower->plant = new plant::Plant;
            flower->plant->vtable = new plant::Plant::PseudoVTable;
            flower->plant->vtable->GetVowelProportion = flower::GetVowelProportion;
            flower->plant->vtable->Input = flower::Input;
            flower->plant->vtable->InputRnd = flower::InputRnd;
            flower->plant->vtable->ToString = flower::ToString;
            if (random) {
                flower->plant->vtable->InputRnd(flower);
            } else {
                flower->plant->vtable->Input(file, flower);
            }
            cont->plants[index] = flower;
        }  else {
            tree::Tree *tree = new tree::Tree;
            tree->plant = new plant::Plant;
            tree->plant->vtable = new plant::Plant::PseudoVTable;
            tree->plant->vtable->GetVowelProportion = tree::GetVowelProportion;
            tree->plant->vtable->Input = tree::Input;
            tree->plant->vtable->InputRnd = tree::InputRnd;
            tree->plant->vtable->ToString = tree::ToString;
            if (random) {
                tree->plant->vtable->InputRnd(tree);
            } else {
                tree->plant->vtable->Input(file,tree);
            }
            cont->plants[index] = tree;
        }
    }
    return true;
}

// Puts the plant data to the selected output-file.
bool Output(FILE * const file, void * const ptr) {
    /* Using the fact that each type of plant uses
     * its own vtable of functions, we can almost
     * guarantee, that reinterpret_cast<> to any
     * of these types will correctly "unbox" the needed
     * function pointers, THUS making it possible
     * to see the data in the original way (in the way
     * it was set in the array). */
    tree::Tree *tree = reinterpret_cast<tree::Tree*>(ptr);
    char *str;
    tree->plant->vtable->ToString(ptr, &str);
    fprintf(file,"%s\n", str);
    //fputs(str, file);
    //fputc('\n', file);
    delete str;
    return true;
}

// Puts the container data to the selected output-file.
bool ContainerOutput(FILE * const file, const PlantContainer * const cont) {
    fprintf(file, "Plant container with %d elements:\n", cont->current_size);
    for(int index = 0; index < cont->current_size; ++index) {
        Output(file, cont->plants[index]);
    }
    return true;
}

// Deallocates memory used by the container struct.
void CLearAndDelete(PlantContainer *data) {
    for (int index = 0; index < data->current_size; ++index) {
        // Data clearing for each specific plant.
        ClearSpace(reinterpret_cast<Tree*>(data->plants[index])->plant);
    }
    delete[] data->plants;
    delete data->plants;
    data->current_size = 0;
}

// Finds a suitable index in the container to put the needed item to.
int ContainerBinarySearch(PlantContainer * const cont, double value_to_comp,
                          int left_border, int right_border) {
    if (left_border >= right_border) {
        return left_border;
    }
    int middle_index = (left_border + right_border) / 2;
    double mid_item_proportion = reinterpret_cast<Tree*>(cont->plants[middle_index])->
            plant->vtable->GetVowelProportion(cont->plants[middle_index]);
    if (value_to_comp == mid_item_proportion) { return middle_index;}
    return ((value_to_comp > mid_item_proportion) ?
        ContainerBinarySearch(cont, value_to_comp, middle_index + 1, right_border) :
                ContainerBinarySearch(cont, value_to_comp, left_border, middle_index));

}

// Sorts the container using Binary Insertion Sort (Insertion Sort with implemented Binary Search O(n*log(n))).
void ContainerBinaryInsertionSort(PlantContainer * const cont) {
    for (int index = 0; index < cont->current_size; ++index) {
        void* copy = cont->plants[index];
        double current_proportion =
                reinterpret_cast<Tree*>(copy)->plant->vtable->GetVowelProportion(copy);
        int new_pos_index = ContainerBinarySearch(cont, current_proportion, 0, index);
        for (int local_index = index - 1; new_pos_index <= local_index; --local_index) {
            cont->plants[local_index + 1] = cont->plants[local_index];
        }
        cont->plants[new_pos_index] = copy;
    }
}


