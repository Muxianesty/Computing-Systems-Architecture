# Just to make sure the program works I decided
# to use softer CMake versions restrictions.
# cmake_minimum_required(VERSION 3.16.3)

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(SecondProject)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
        # Main source file
        main.cpp
        # "Plant"-class files
        "Plant-entity classes/Plant.cpp" "Plant-entity classes/Plant.h"
        # "Tree"-class files
        "Plant-entity classes/Tree.cpp" "Plant-entity classes/Tree.h"
        # "Bush"-class files
        "Plant-entity classes/Bush.cpp" "Plant-entity classes/Bush.h"
        # "Flower"-class files
        "Plant-entity classes/Flower.cpp" "Plant-entity classes/Flower.h"
        # "PlantContainer"-class files
        "PlantContainer.cpp" "PlantContainer.h")

# Optional sanitizer params to check memory deallocation processes.
# set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all"
#         CACHE STRING "Compiler flags in asan build"
#         FORCE)

add_executable(SecondProject ${SOURCES})
