cmake_minimum_required(VERSION 3.9)

project(SkullKingCliApp)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE SkullKingLib)

# Tell C++ compiler to use C++20 features. We don't actually use any of them.
target_compile_features(main PUBLIC cxx_std_17)