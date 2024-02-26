cmake_minimum_required(VERSION 3.5)
project(tp1_algo3)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCE_FILES src/*.cpp sr/*.h)
file(GLOB TEST_FILES test/*.cpp)

SET(BUILD_GMOCK OFF)
SET(BUILD_GTEST ON)
add_library(gtest STATIC test/gtest-1.8.1/gtest-all.cc)
add_library(gtest_main STATIC test/gtest-1.8.1/gtest_main.cc)

include_directories(.)

add_executable(correrTest ${SOURCE_FILES} ${TEST_FILES} test/test_exp.cpp)

target_link_libraries(correrTest gtest gtest_main)

add_test(correrTest experimentaciones)