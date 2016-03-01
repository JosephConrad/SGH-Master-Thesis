cmake_minimum_required(VERSION 2.8)
set(PROJECT_NAME_STR heston)
project(${PROJECT_NAME_STR} C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(BASEPATH "${CMAKE_SOURCE_DIR}")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(GEN_DIR "{PROJECT_SOURCE_DIR}/gen")
set(TEST_DIR "{PROJECT_SOURCE_DIR}/test")

#############################
#       Optimization
#############################
# set(CMAKE_CXX_FLAGS_DEBUG "-O2")
# set(CMAKE_C_FLAGS_DEBUG "-O2")

include(src/main/CMakeLists.txt)
include(src/test/CMakeLists.txt)