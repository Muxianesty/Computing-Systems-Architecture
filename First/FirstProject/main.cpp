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
#define TESTS_PATH "..\..\Tests\\"

int main(int argc, char* argv[]) {
    // Variant 97 -> Task 13("Plant"), Sort function 7("Binary insertion").
    if (argc != 5 || (strcmp(argv[1], "-r") && strcmp(argv[1], "-f"))) {
        printf("%s\nUse %s\nor %s\n", COMM_ERROR, COMM_TEMPLATE1, COMM_TEMPLATE2);
        return 0;
    }
    FILE *first_input = fopen(argv[2], "r");
    FILE *first_output = fopen(argv[3], "w+");
    FILE *second_output = fopen(argv[4], "w+");
    PlantContainer data;
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
    InitializeContainer(&data, size);
    printf("Filling container...\n");
    // Selecting a way to initialize the array itself (on random or from file).
    if (!strcmp(argv[1], "-r")) {
        srand(time(0));
        InputFromFileOrRnd(first_input, &data, true);
    } else {
        InputFromFileOrRnd(first_input, &data, false);
    }
    printf("Container filled. Printing in file...\n");
    // First output in the file.
    ContainerOutput(first_output, &data);
    printf("Container printed. Sorting the container...\n");
    // Binary insertion sorting (function 7).
    ContainerBinaryInsertionSort(&data);
    printf("Container sorted. Printing in file...");
    // Second output in the file.
    ContainerOutput(second_output, &data);
    /* The following block of code
     * is quite important, as it
     * serves as a means of "pointer
     * deleting" and memory deallocating
     * (it is hidden within #pragma region directive). */
    #pragma region
    CLearAndDelete(&data);
    fclose(first_input);
    fclose(first_output);
    fclose(second_output);
    delete first_input;
    delete first_output;
    delete second_output;
    #pragma endregion
    return 0;
}
