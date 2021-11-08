# ------------------------------------------------------------------------------
# main.py - provides a starting point for the program itself.
# ------------------------------------------------------------------------------

from PlantContainer import *
import sys
import time


def errorMessage() -> str:
    """
    Additional function to return a string message containing info about
    the possible command line argument-templates.
    """
    return "Incorrect command input/qualifier\n" \
           "Use\n\"main.py -r quantity output1.txt output2.txt\"\nor\n" \
           "\"main.py -f input1.txt output1.txt output2.txt\""


if __name__ == '__main__':
    # Variant 97 -> Task 13("Plant"), Sort function 7("Binary insertion").
    start_time = time.time()
    if (sys.argv.__len__() != 5) or ((sys.argv[1] != "-r") and (sys.argv[1] != "-f")):
        print(errorMessage())
        sys.exit()
    # Unlike with C-like languages, open()-function generates an error whenever no file
    # with the specified name exists, thus we need to add additional checking for a situation
    # of random-generated values (when the second param is not a file-path).
    try:
        first_input = 0
        first_input = open(sys.argv[2], "r")
    except FileNotFoundError:
        if sys.argv[1] == "-f":
            print(f"No file {sys.argv[2]} was found")
            sys.exit()
    first_output = open(sys.argv[3], "w+")
    second_output = open(sys.argv[4], "w+")
    # Selecting a way to initialize the size of the array (from args or from file).
    size = int(sys.argv[2] if (sys.argv[1] == "-r") else (first_input.readline()))
    container = PlantContainer(size)

    print("Filling container...\n")
    container.inputFromFileOrRnd((sys.argv[1] == "-r"), first_input)

    print("Container filled. Printing in file...\n")
    # First output to the file.
    container.containerOutput(first_output)

    print("Container printed. Sorting the container...\n")
    # Binary-insertion sorting.
    container.containerBinaryInsertionSort()

    print("Container sorted. Printing in file...\n")
    # Second output to the file.
    container.containerOutput(second_output)

    print(f"-> {(time.time() - start_time) * 1000: .4f}ms elapsed")

    # Closing the output to the files (plus checking if input-file was initialized beforehand).
    if first_input != 0:
        first_input.close()
    first_output.close()
    second_output.close()
