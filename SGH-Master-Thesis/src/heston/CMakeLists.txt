cmake_minimum_required(VERSION 3.2)
project(heston)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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
                MonteCarlo/MCHeston.cpp MonteCarlo/MCHeston.h
                main.cpp option.h option.cpp HestonModel/header/HestonEuler.h HestonModel/src/HestonEuler.cpp payoff.h payoff.cpp statistics.h statistics.cpp correlated_snd.h correlated_snd.cpp
                MonteCarlo/MCHeston.cpp MonteCarlo/MCHeston.h
                SimpleMonteCarlo/MCBlackScholes.cpp SimpleMonteCarlo/MCBlackScholes.h SimpleMonteCarlo/PolarGenerator.cpp SimpleMonteCarlo/PolarGenerator.h OrderBook/OrderBook.cpp
                OrderBook/OrderBook.h OrderBook/Order.cpp OrderBook/Order.h OrderBook/Operation.h HestonModel/src/HestonAndersen.cpp HestonModel/header/HestonAndersen.h HestonModel/src/Heston.cpp HestonModel/header/Heston.h)
        target_link_libraries(heston ${Boost_LIBRARIES})
endif()
