# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.9)

project(
    SkullKingLib
    VERSION 0.1
    DESCRIPTION "Skull King game library")

add_library(SkullKingLib src/SkullKingLib.cpp src/Game.cpp src/Card.cpp src/Player.cpp)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS True)

set_target_properties(SkullKingLib PROPERTIES SOVERSION 1)
set_target_properties(SkullKingLib PROPERTIES PUBLIC_HEADER include/SkullKingLib.h)

# PUBLIC needed to make both hello.h and hello library available elsewhere in project
target_include_directories(SkullKingLib PUBLIC include)

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
target_compile_features(SkullKingLib PUBLIC cxx_std_17)