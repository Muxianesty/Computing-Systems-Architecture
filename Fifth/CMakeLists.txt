cmake_minimum_required(VERSION 3.16)
project(Fifth)

set(CMAKE_CXX_STANDARD 20)

add_executable(Fifth main.cpp Entities/Bee.cpp Entities/Bee.h Entities/Hive.cpp Entities/Hive.h Entities/WinniePooh.cpp Entities/WinniePooh.h)
