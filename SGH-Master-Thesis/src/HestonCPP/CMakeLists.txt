cmake_minimum_required(VERSION 2.8)
project(heston)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(BASEPATH "${CMAKE_SOURCE_DIR}")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(GEN_DIR "{PROJECT_SOURCE_DIR}/gen")
include_directories("${BASEPATH}")

# Directories configuration
#set(PROJECT_BINARY_DIR "${PROJECT_SOURCE_DIR}/build")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
#set(CMAKE_CXX_FLAGS_DEBUG "-O2")
#set(CMAKE_C_FLAGS_DEBUG "-O2")

find_package(Boost 1.55.0 COMPONENTS system filesystem REQUIRED)

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
                src/main/cpp/bs/BlackScholesAnalytic.h)
        target_link_libraries(heston ${Boost_LIBRARIES})
endif()
