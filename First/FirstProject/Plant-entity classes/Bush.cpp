//------------------------------------------------------------------------------
// Bush.cpp - provides implementation for the bush-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Bush.h"

// Gets the correctly interpreted vowel count proportion (for bush).
double bush::GetVowelProportion(void * const ptr) {
    return reinterpret_cast<Bush*>(ptr)->plant->vowel_count_proportion;
}

// Sets the data of a bush with file-typed values.
bool bush::Input(FILE * const file, void * const ptr) {
    Bush *new_ptr = reinterpret_cast<Bush*>(ptr);
    Input(file, new_ptr->plant);
    int month_id;
    fscanf(file, "%d", &month_id);
    month_id = abs(month_id);
    month_id = ((month_id > 12 || !month_id) ? month_id % 12 + 1 : month_id);
    new_ptr->month = static_cast<Bush::BlossomMonth>(month_id);
    return true;
}

// Sets the data of a bush with random-generated values.
bool bush::InputRnd(void * const ptr) {
    Bush *new_ptr = reinterpret_cast<Bush*>(ptr);
    InputRnd(new_ptr->plant);
    new_ptr->month = static_cast<Bush::BlossomMonth>(rand() % 12 + 1);
    return true;
}

// Sets the C-string-type data of a given bush into a char**-pointer.
bool bush::ToString(const void * const ptr, char* *data) {
    const Bush *new_ptr = reinterpret_cast<const Bush*>(ptr);
    char *plant_data;
    ToString(new_ptr->plant, &plant_data);
    char *month_data = new char[21];
    GetMonth(new_ptr, &month_data);
    *data = new char[101];
    snprintf(*data, 100, "Bush %s:%s", plant_data, month_data);
    (*data)[100] = '\0';
    delete [] plant_data;
    delete [] month_data;
    return true;
}

// Gets a C-string representation of a month of blossom of a specific bush.
bool bush::GetMonth(const Bush * const bush, char* *data) {
    //*data = new char[21];
    int symbols_count;
    switch(bush->month) {
        case Bush::BlossomMonth::January: symbols_count = snprintf(*data, 20, "January"); break;
        case Bush::BlossomMonth::February: symbols_count = snprintf(*data, 20, "February"); break;
        case Bush::BlossomMonth::March: symbols_count = snprintf(*data, 20,"March"); break;
        case Bush::BlossomMonth::April: symbols_count = snprintf(*data, 20,"April"); break;
        case Bush::BlossomMonth::May: symbols_count = snprintf(*data, 20,"May"); break;
        case Bush::BlossomMonth::June: symbols_count = snprintf(*data,20, "June"); break;
        case Bush::BlossomMonth::July: symbols_count = snprintf(*data,20, "July"); break;
        case Bush::BlossomMonth::August: symbols_count = snprintf(*data, 20,"August"); break;
        case Bush::BlossomMonth::September: symbols_count = snprintf(*data,20, "September"); break;
        case Bush::BlossomMonth::October: symbols_count = snprintf(*data, 20,"October"); break;
        case Bush::BlossomMonth::November: symbols_count = snprintf(*data,20, "November"); break;
        case Bush::BlossomMonth::December: symbols_count = snprintf(*data, 20,"December"); break;
    }
    (*data)[symbols_count] = '\0';
    return true;
}