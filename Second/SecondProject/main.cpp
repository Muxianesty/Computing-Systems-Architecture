//------------------------------------------------------------------------------
// main.cpp - provides a single function int main(int, char**), used as a
// starting point for the program itself.
//------------------------------------------------------------------------------

#include "stdio.h"
#include "string.h"
#include "PlantContainer.h"

#define COMM_ERROR "Incorrect command input/qualifier"
#define COMM_TEMPLATE1 "prog.exe -r quantity output1.txt output2.txt"
#define COMM_TEMPLATE2 "prog.exe -f input1.txt output1.txt output2.txt"

int main(int argc, char *argv[]) {
    // Variant 97 -> Task 13("Plant"), Sort function 7("Binary insertion").

    // clock_t time_ = clock();
    if (argc != 5 || (strcmp(argv[1], "-r") && strcmp(argv[1], "-f"))) {
        printf("%s\nUse %s\nor %s\n", COMM_ERROR, COMM_TEMPLATE1, COMM_TEMPLATE2);
        return 0;
    }

    FILE *first_input = fopen(argv[2], "r");
    FILE *first_output = fopen(argv[3], "w+");
    FILE *second_output = fopen(argv[4], "w+");
    int size;
    // Selecting a way to initialize the size of the array (from args or from file).
    if (!strcmp(argv[1], "-r")) {
        size = atoi(argv[2]);
    } else {
        if (feof(first_input)) {
            size = 0;
        } else {
            fscanf(first_input, "%d", &size);
        }
    }
    PlantContainer data = PlantContainer(size);

    printf("Filling container...\n");
    // Selecting a way to initialize the array itself (on random or from file).
    if (!strcmp(argv[1], "-r")) {
        srand(time(0));
    }
    data.inputFromFileOrRnd(first_input, !strcmp(argv[1], "-r"));

    printf("Container filled. Printing in file...\n");
    // First output in the file.
    data.containerOutput(first_output);

    printf("Container printed. Sorting the container...\n");
    // Binary insertion sorting (function 7).
    data.containerBinaryInsertionSort();

    printf("Container sorted. Printing in file...");
    // Second output in the file.
    data.containerOutput(second_output);
    // printf("\n -> %ld", clock() - time_);

    /* The following block of code
     * is quite important, as it
     * serves as a means of "pointer
     * deleting" and memory deallocating
     * (it is hidden within #pragma region directive). */
#pragma region
    /* Additional checking whether first_input is null or not
     * (removing the ternary("if")-operator may result in program errors). */
    (first_input) ? fclose(first_input) : 0;
    fclose(first_output);
    fclose(second_output);
    /* Somehow while running the program on WSL, it crashes while executing the following
     * lines of code, thus I decided to comment them (turns out, on WSL-systems fclose() is
     * equivalent to delete-operator). */
    // delete first_input;
    // delete first_output;
    // delete second_output;
#pragma endregion
    return 0;
}
