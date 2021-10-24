//------------------------------------------------------------------------------
// Bush.cpp - provides implementation for the bush-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Bush.h"

// Default "bush"-object constructor.
Bush::Bush() : Plant() {
    this->month_ = BlossomMonth::January;
}

/* Special constructor, which has different ways of creating a
 * "bush"-object depending on what type of input was selected. */
Bush::Bush(bool from_file, FILE *file) : Plant(from_file, file) {
    if (from_file) {
        int month_id;
        fscanf(file, "%d", &month_id);
        month_id = abs(month_id);
        month_id = ((month_id > 12 || !month_id) ? month_id % 12 + 1 : month_id);
        this->month_ = static_cast<Bush::BlossomMonth>(month_id);
    } else {
        this->month_ = static_cast<Bush::BlossomMonth>(rand() % 12 + 1);
    }
}


// Sets the C-string-type data of a given bush into a char**-pointer.
char *Bush::toString() {
    char *plant_data = static_cast<Plant>(*this).toString();
    char *month_data = this->getMonth();
    char *data = new char[101];
    data[100] = '\0';
    int print_count = snprintf(data, 100, "Bush %s:%s", plant_data, month_data);
    data[print_count] = '\0';
    delete [] plant_data;
    delete [] month_data;
    return data;
}

// Gets a C-string representation of a month of blossom of a specific bush.
char *Bush::getMonth() {
    char *data = new char[21];
    data[20] = '\0';
    int symbols_count;
    switch(this->month_) {
        case Bush::BlossomMonth::January: symbols_count = snprintf(data, 20, "January"); break;
        case Bush::BlossomMonth::February: symbols_count = snprintf(data, 20, "February"); break;
        case Bush::BlossomMonth::March: symbols_count = snprintf(data, 20,"March"); break;
        case Bush::BlossomMonth::April: symbols_count = snprintf(data, 20,"April"); break;
        case Bush::BlossomMonth::May: symbols_count = snprintf(data, 20,"May"); break;
        case Bush::BlossomMonth::June: symbols_count = snprintf(data,20, "June"); break;
        case Bush::BlossomMonth::July: symbols_count = snprintf(data,20, "July"); break;
        case Bush::BlossomMonth::August: symbols_count = snprintf(data, 20,"August"); break;
        case Bush::BlossomMonth::September: symbols_count = snprintf(data,20, "September"); break;
        case Bush::BlossomMonth::October: symbols_count = snprintf(data, 20,"October"); break;
        case Bush::BlossomMonth::November: symbols_count = snprintf(data,20, "November"); break;
        case Bush::BlossomMonth::December: symbols_count = snprintf(data, 20,"December"); break;
    }
    data[symbols_count] = '\0';
    return data;
}