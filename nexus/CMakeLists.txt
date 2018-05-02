cmake_minimum_required(VERSION 3.9)
project(final_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(tests src/utility.cpp src/utility.h src/constants.h tests/utility-tests.cpp tests/catch.hpp)