#-------------------
# Test
#-------------------
find_package(Threads REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/build/ext/gtest/src/googletest/googletest/include)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/src/main/cpp/tools/config)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

add_subdirectory(${EXT_PROJECTS_DIR}/gtest)
add_definitions(${MSVC_COMPILER_DEFS})

enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
include_directories("${BASEPATH}")

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/src/test/cpp/config/*.cpp )
add_executable(${PROJECT_TEST_NAME}
        ${TEST_SRC_FILES}
        src/main/cpp/tools/config/Config.cpp
        src/main/cpp/tools/config/Config.h)
add_dependencies(${PROJECT_TEST_NAME} googletest)

target_link_libraries(${PROJECT_TEST_NAME}
        ${GTEST_LIBS_DIR}/libgtest.a
        ${GTEST_LIBS_DIR}/libgtest_main.a
        )

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})

add_test(configTest ${PROJECT_TEST_NAME})
