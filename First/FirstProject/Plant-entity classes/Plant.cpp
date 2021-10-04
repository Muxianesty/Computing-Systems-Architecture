//------------------------------------------------------------------------------
// Plant.cpp - provides implementation for the plant-struct
// and functions working with it.
//------------------------------------------------------------------------------
#include "Plant.h"
#include "stdio.h"


// Sets the data of a plant with file-typed values.
bool plant::Input(FILE * file, plant::Plant * const plant) {
    plant->name = new char[21];
    fscanf(file, "%20s", plant->name);
    plant->name_length = strlen(plant->name);
    plant->vowel_count_proportion = CountVowelProportion(plant);
    return true;
}

// Sets the data of a plant with random-generated values.
bool plant::InputRnd(Plant * const plant) {
    plant->name_length = rand() % 20 + 1;
    RandomName(plant->name_length, &plant->name);
    plant->vowel_count_proportion = CountVowelProportion(plant);
    return true;
}

// Sets the C-string-type data of a given plant into a char**-pointer.
bool plant::ToString(const Plant * const plant, char* *data) {
    *data = new char[plant->name_length + 31];
    snprintf(*data, plant->name_length + 30, "%s:VowelInNameProportion=%4.2f",
            plant->name, plant->vowel_count_proportion);
    (*data)[plant->name_length + 30] = '\0';
    return true;
}
// Counts the fraction of a type ("count of vowels"/"name length").
double plant::CountVowelProportion(Plant * const plant) {
    int vowel_count = 0;
    for (int index = 0; index < plant->name_length; ++index) {
        vowel_count += ((IsAVowel(&plant->name[index])) ? 1 : 0);
    }
    plant->vowel_count_proportion =
            static_cast<double>(vowel_count) / plant->name_length;
    return plant->vowel_count_proportion;
}

// Determines if a given character is a vowel.
bool plant::IsAVowel(const char *ch) {
    char temp = tolower(*ch);
    switch (temp) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'y':
        case 'u': return true;
        default: return false;
    }
}
// Deallocates memory used by the plant-structure.
bool plant::ClearSpace(Plant *plant_to_clear) {
    delete [] plant_to_clear->name;
    delete [] plant_to_clear->vtable;
    plant_to_clear->name_length = 0;
    return true;
}

// Generates a random name of a given length (characters vary from 'a' to 'z' in ASCII).
bool plant::RandomName(int name_length, char* *data) {
    if (name_length <= 0) {
        *data = nullptr;
        return false;
    }
    *data = new char[name_length + 1];
    for (int index = 0; index < name_length; ++index) {
        (*data)[index] = static_cast<char>(rand() % 26 + 97);
    }
    (*data)[name_length] = '\0';
    return true;
}