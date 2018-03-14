cmake_minimum_required(VERSION 3.5)
project(naivebayes)

set(CMAKE_CXX_STANDARD 14)

add_executable(naivebayes src/feature_vector.cpp  src/training_module.cpp src/main.cpp src/test.cpp tests/test.h)
#add_executable(unit-tests)
