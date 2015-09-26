cmake_minimum_required(VERSION 3.2)
project(heston)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES heston)
add_executable(${SOURCE_FILES} main.cpp option.h option.cpp heston_mc.h heston_mc.cpp payoff.h payoff.cpp statistics.h statistics.cpp correlated_snd.h correlated_snd.cpp)