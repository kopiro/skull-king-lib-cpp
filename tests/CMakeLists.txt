cmake_minimum_required(VERSION 3.9)

project(SkullKingTests)

include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
	tests
	tests.cpp
)
target_link_libraries(
	tests
	GTest::gtest_main
	SkullKingLib
)

target_compile_features(tests PUBLIC cxx_std_17)

include(GoogleTest)
gtest_discover_tests(tests)
