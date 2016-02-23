#-------------------
# Test
#-------------------
add_definitions(${MSVC_COMPILER_DEFS})
enable_testing()
set(PROJECT_TEST_NAME_TEST hestontest)

#file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/config/*.cpp)
add_executable(${PROJECT_TEST_NAME_TEST}
        cpp/config/ConfigTest.cpp)
#add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})


if(NOT WIN32)
    target_link_libraries(${PROJECT_TEST_NAME_TEST}
            ${GTEST_LIBS_DIR}/libgtest.a
            ${GTEST_LIBS_DIR}/libgtest_main.a
            )
else()
    target_link_libraries(${PROJECT_TEST_NAME_TEST}
            debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
            optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
            )
    target_link_libraries(${PROJECT_TEST_NAME_TEST}
            debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
            optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
            )
endif()

target_link_libraries(${PROJECT_TEST_NAME_TEST} ${CMAKE_THREAD_LIBS_INIT})

add_test(test1 ${PROJECT_TEST_NAME_TEST})