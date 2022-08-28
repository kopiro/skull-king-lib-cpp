# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.9)

project(
    SkullKing
    VERSION 0.1
    DESCRIPTION "Small CMake example built with VSCode")

add_subdirectory(lib)
add_subdirectory(apps)