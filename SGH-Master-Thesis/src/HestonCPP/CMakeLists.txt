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


include_directories("${BASEPATH}")
include_directories("${BASEPATH}")

set(PROJECT_BINARY_DIR "${PROJECT_SOURCE_DIR}/build")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

find_package(Boost 1.55.0 COMPONENTS system filesystem REQUIRED)
find_package(Threads REQUIRED)

# Build protocol buffers
add_custom_command(
        OUTPUT ${GEN_DIR}/execute.pb.cc ${GEN_DIR}/execute.pb.h
        COMMAND protoc -I=${PROTO_DIR} --cpp_out=${GEN_DIR} ${PROTO_DIR}/execute.proto
        DEPENDS ${PROTO_DIR}/execute.proto
)

if(Boost_FOUND)

        message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
        message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
        message(STATUS "Boost_VERSION: ${Boost_VERSION}")
        include_directories(${Boost_INCLUDE_DIRS})

endif()


if(CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-Wall -ansi -Wno-deprecated -pthread)
endif()

if(MSVC)
        #vc 2012 fix for vararg templates
        set(MSVC_COMPILER_DEFS "-D_VARIADIC_MAX=10")
endif()

#-------------------
# set common include folder for module
#-------------------
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

#-------------------
# Module source
#-------------------
if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        set(SOURCE_FILES heston)
        add_executable(${SOURCE_FILES}
                main.cpp
                src/main/cpp/option/option.h
                src/main/cpp/option/option.cpp
                src/main/cpp/heston/src/HestonEuler.cpp
                src/main/cpp/payoff/payoff.h
                src/main/cpp/payoff/payoff.cpp
                src/main/cpp/statistics/statistics.h
                src/main/cpp/statistics/statistics.cpp
                src/main/cpp/correlated/correlated_snd.h
                src/main/cpp/correlated/correlated_snd.cpp
                src/main/cpp/bs/MCBlackScholes.cpp
                src/main/cpp/bs/MCBlackScholes.h
                src/main/cpp/random/PolarGenerator.cpp
                src/main/cpp/random/PolarGenerator.h
                src/main/cpp/mc/MonteCarloSimulation.cpp
                src/main/cpp/mc/MonteCarloSimulation.h
                src/main/cpp/heston/src/HestonAndersenMartingale.cpp
                src/main/cpp/heston/src/HestonExact.cpp
                src/main/cpp/heston/src/HestonMC.cpp
                src/main/cpp/heston/src/Heston.cpp
                src/main/cpp/heston/src/HestonAndersen.cpp
                src/main/cpp/heston/src/HestonMC.cpp
                src/main/cpp/heston/header/HestonAndersen.h
                src/main/cpp/heston/header/HestonMC.h
                src/main/cpp/heston/header/HestonExact.h
                src/main/cpp/heston/header/Heston.h
                src/main/cpp/heston/header/HestonEuler.h
                src/main/cpp/heston/header/HestonAndersenMartingale.h
                src/main/cpp/bs/BlackScholesAnalytic.cpp
                src/main/cpp/bs/BlackScholesAnalytic.h
                src/main/cpp/simulation/Simulation.cpp
                src/main/cpp/simulation/Simulation.h
                src/main/cpp/tools/config/Config.cpp
                src/main/cpp/tools/config/Config.h
                src/main/cpp/tools/output/OutputAndConsole.cpp
                src/main/cpp/tools/output/OutputAndConsole.h)
        target_link_libraries(heston ${Boost_LIBRARIES})
endif()


#
#add_definitions(${MSVC_COMPILER_DEFS})
#enable_testing()
#set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
#include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
#
#file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/cpp/config/*.cpp)
#add_executable(${PROJECT_TEST_NAME} src/test/cpp/config/ConfigTest.cpp)
#add_dependencies(${PROJECT_TEST_NAME} googletest)
##
#
#if(NOT WIN32)
#        target_link_libraries(${PROJECT_TEST_NAME}
#                ${GTEST_LIBS_DIR}/libgtest.a
#                ${GTEST_LIBS_DIR}/libgtest_main.a
#                )
#else()
#        target_link_libraries(${PROJECT_TEST_NAME}
#                debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
#                optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
#                )
#        target_link_libraries(${PROJECT_TEST_NAME}
#                debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
#                optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
#                )
#endif()

#target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})
#
#

#
#####################################################################
## Configure the test to use GoogleTest
##
## If used often, could be made a macro.
#####################################################################
#
#add_dependencies(heston gtest)
#include_directories(${source_dir}/include)
#target_link_libraries(heston ${binary_dir}/libgtest.a)
#target_link_libraries(heston ${binary_dir}/libgtest_main.a)
#
#
#####################################################################
## Just make the test runnable with
##   $ make test
#####################################################################
#
#enable_testing()
#add_test(NAME heston
#        COMMAND heston)
#
#

find_package(Threads REQUIRED)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

add_subdirectory(${EXT_PROJECTS_DIR}/gtest)


#-------------------
# Test
#-------------------
add_definitions(${MSVC_COMPILER_DEFS})
enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
include_directories(${PROJECT_SOURCE_DIR}/build/src/gtest/googletest/include)

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/src/test/cpp/config/*.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
add_dependencies(${PROJECT_TEST_NAME} googletest)

target_link_libraries(${PROJECT_TEST_NAME}
        ${GTEST_LIBS_DIR}/libgtest.a
        ${GTEST_LIBS_DIR}/libgtest_main.a
        )

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})

add_test(test1 ${PROJECT_TEST_NAME})
