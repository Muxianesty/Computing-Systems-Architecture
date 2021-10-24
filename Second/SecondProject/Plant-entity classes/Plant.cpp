//------------------------------------------------------------------------------
// Plant.cpp - provides implementation for the plant-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Plant.h"
#include "string.h"
#include "stdio.h"

// Extracts data from a vowel count proportion-field, declared "private".
double Plant::getProportion() const {
    return this->vowel_count_proportion_;
}

// Counts vowel count proportion for a plant (instance method).
void Plant::countVowelProportion() {
    int vowel_count = 0;
    for (int index = 0; index < this->name_length_; ++index) {
        vowel_count += ((isAVowel(&this->name_[index])) ? 1 : 0);
    }
    this->vowel_count_proportion_ =
            static_cast<double>(vowel_count) / this->name_length_;
}

// Default "plant"-object constructor.
Plant::Plant() {
    this->name_ = nullptr;
    this->name_length_ = 0;
    this->vowel_count_proportion_ = 0;
}

/* (I had to use a ref('&') in order to define a copying constructor.)
 * Special constructor, which is used whenever we need to extract "plant"-data
 * from an object of a derived class (otherwise default copying constructor copies
 * the name-field pointer thus leading to errors when invoking destructor). */
Plant::Plant(const Plant &plant) : Plant() {
    this->name_length_ = plant.name_length_;
    this->vowel_count_proportion_ = plant.vowel_count_proportion_;
    this->name_ = new char[21];
    int index = 0;
    for (; index < this->name_length_; ++index) {
        this->name_[index] = plant.name_[index];
    }
    this->name_[index] = '\0';
}

/* Special constructor, which has different ways of creating a
 * "plant"-object depending on what type of input was selected. */
Plant::Plant(bool from_file, FILE *file) : Plant() {
    if (from_file) {
        this->name_ = new char[21];
        this->name_[20] = '\0';
        fscanf(file, "%20s", this->name_);
    } else {
        this->name_ = randomName(rand() % 20 + 1);
    }
    this->name_length_ = strlen(this->name_);
    this->countVowelProportion();
}


// Default destructor for the "plant"-object.
Plant::~Plant() {
    delete[] this->name_;
}

// Puts the plant data to the selected output-file.
void Plant::output(FILE *const file) {
    char *str = this->toString();
    fprintf(file, "%s\n", str);
    //fputs(str, file);
    //fputc('\n', file);
    delete str;
}

/* Virtual method, which is unique for each class, derived from "Plant". Is used
 * to collect C-string type data about a plant. */
char *Plant::toString() {
    char *data = new char[this->name_length_ + 31];
    snprintf(data, this->name_length_ + 30, "%s:VowelInNameProportion=%4.2f",
             this->name_, this->vowel_count_proportion_);
    data[this->name_length_ + 30] = '\0';
    return data;
}

// Determines if a given character is a vowel.
bool isAVowel(const char *ch) {
    char temp = tolower(*ch);
    switch (temp) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'y':
        case 'u':
            return true;
        default:
            return false;
    }
}

// Generates a random name of a given length (characters vary from 'a' to 'z' in ASCII).
char *randomName(int name_length) {
    if (name_length <= 0) {
        return nullptr;
    }
    char *data = new char[21];
    data[20] = '\0';
    for (int index = 0; index < name_length; ++index) {
        data[index] = static_cast<char>(rand() % 26 + 97);
    }
    data[name_length] = '\0';
    return data;
}