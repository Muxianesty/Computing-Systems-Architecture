cmake_minimum_required(VERSION 3.20)
project(FirstProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(FirstProject main.cpp "Plant-entity classes/Plant.cpp" "Plant-entity classes/Plant.h" "Plant-entity classes/Tree.cpp" "Plant-entity classes/Tree.h" "Plant-entity classes/Bush.cpp" "Plant-entity classes/Bush.h" "Plant-entity classes/Flower.cpp" "Plant-entity classes/Flower.h" "PlantContainer.cpp" "PlantContainer.h")
