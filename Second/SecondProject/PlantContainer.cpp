//------------------------------------------------------------------------------
// PlantContainer.cpp - provides implementation for the container of plants_-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "PlantContainer.h"

// Default "plant-container"-object constructor.
PlantContainer::PlantContainer() {
    this->current_size_ = 0;
    this->capacity_ = 0;
    this->plants_ = nullptr;
}

// Default "plant-container"-object constructor for a specific capacity.
PlantContainer::PlantContainer(int capacity) : PlantContainer() {
    if (capacity < 0 || capacity > PlantContainer::kMax_size) {
        printf("!!Value %d is less than 0 or higher than 10000 and cannot be used as!!\n", capacity);
        printf("!!as container capacity_ - value '0' will be used instead!!");
        capacity = 0;
    }
    this->plants_ = new Plant *[capacity];
    this->capacity_ = capacity;
    this->current_size_ = 0;
}

// Deallocates memory used by the container class.
PlantContainer::~PlantContainer() {
    /* !!! delete-operator invokes "Plant"-destructors, but if the program crashes during
     * its runtime - try removing commentaries from the for-cycle block AND
     * add commentaries to the "delete[] this->plants_;"-line. !!!*/

    //for (int plant_index = 0; plant_index < this->current_size_; ++plant_index) {
    //    delete this->plants_[plant_index];
    //}
    delete[] this->plants_;
    this->current_size_ = 0;
    this->capacity_ = 0;
}

// Fills the container depending on the flag (with random values or from file).
bool PlantContainer::inputFromFileOrRnd(FILE *file, bool random) {
    for (int index = 0; index < this->capacity_ && (random || !feof(file)); ++index) {
        int rnd_type_id;
        // Deducing a given type given by the selected way of input.
        if (random) {
            rnd_type_id = rand() % 3 + 1;
        } else {
            fscanf(file, "%d", &rnd_type_id);
            rnd_type_id = abs(rnd_type_id);
            rnd_type_id = ((rnd_type_id > 3 || !rnd_type_id) ? rnd_type_id % 3 + 1 : rnd_type_id);
        }
        switch (rnd_type_id) {
            case 1:
                this->plants_[this->current_size_++] = new Bush(!random, file);
                break;
            case 2:
                this->plants_[this->current_size_++] = new Flower(!random, file);
                break;
            case 3:
                this->plants_[this->current_size_++] = new Tree(!random, file);
                break;
            default:
                break;
        }
    }
    return true;
}

// Puts the container data to the selected output-file.
bool PlantContainer::containerOutput(FILE *file) {
    fprintf(file, "Plant container with %d elements:\n", this->current_size_);
    for (int index = 0; index < this->current_size_; ++index) {
        this->plants_[index]->output(file);
    }
    return true;
}

// Finds a suitable index in the container to put the needed item to.
int PlantContainer::containerBinarySearch(double value_to_comp, int left_border,
                                          int right_border) {
    if (left_border >= right_border) {
        return left_border;
    }
    int middle_index = (left_border + right_border) / 2;
    const double mid_item_proportion = this->plants_[middle_index]->getProportion();
    if (value_to_comp == mid_item_proportion) { return middle_index; }
    return ((value_to_comp > mid_item_proportion) ?
            containerBinarySearch(value_to_comp, middle_index + 1, right_border) :
            containerBinarySearch(value_to_comp, left_border, middle_index));

}

// Sorts the container using Binary Insertion Sort (Insertion Sort with implemented Binary Search O(n*log(n))).
void PlantContainer::containerBinaryInsertionSort() {
    for (int index = 0; index < this->current_size_; ++index) {
        Plant *copy = this->plants_[index];
        double current_proportion = copy->getProportion();
        int new_pos_index = containerBinarySearch(current_proportion, 0, index);
        for (int local_index = index - 1; new_pos_index <= local_index; --local_index) {
            this->plants_[local_index + 1] = this->plants_[local_index];
        }
        this->plants_[new_pos_index] = copy;
    }
}


