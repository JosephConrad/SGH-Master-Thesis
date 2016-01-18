cmake_minimum_required(VERSION 3.2)
project(heston)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(BASEPATH "${CMAKE_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${BASEPATH}")

find_package(Boost 1.58.0 COMPONENTS system filesystem REQUIRED)

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
                main.cpp src/main/cpp/option/option.h src/main/cpp/option/option.cpp src/main/cpp/heston/header/HestonEuler.h src/main/cpp/heston/src/HestonEuler.cpp src/main/cpp/payoff/payoff.h src/main/cpp/payoff/payoff.cpp src/main/cpp/statistics/statistics.h src/main/cpp/statistics/statistics.cpp src/main/cpp/correlated/correlated_snd.h src/main/cpp/correlated/correlated_snd.cpp
                src/main/cpp/bs/MCBlackScholes.cpp src/main/cpp/bs/MCBlackScholes.h src/main/cpp/random/PolarGenerator.cpp src/main/cpp/random/PolarGenerator.h
                src/main/cpp/heston/src/HestonAndersen.cpp src/main/cpp/heston/header/HestonAndersen.h src/main/cpp/heston/src/Heston.cpp src/main/cpp/heston/header/Heston.h src/main/cpp/mc/MonteCarloSimulation.cpp src/main/cpp/mc/MonteCarloSimulation.h src/main/cpp/heston/src/HestonAndersenMartingale.cpp src/main/cpp/heston/header/HestonAndersenMartingale.h)
        target_link_libraries(heston ${Boost_LIBRARIES})
endif()
