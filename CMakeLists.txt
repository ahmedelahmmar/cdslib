cmake_minimum_required(VERSION 3.29)
project(cds)

file(GLOB_RECURSE TEST_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE ENTRY_FILE ${PROJECT_SOURCE_DIR}/main.c)

set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)

include_directories(${PROJECT_SOURCE_DIR}/src/inc)

# CppUTest
include(FetchContent)
FetchContent_Declare(
    CppUTest
    GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    GIT_TAG        master # or use release tag, eg. v4.0
)
# Set this to ON if you want to have the CppUTests in your project as well.
set(TESTS OFF CACHE BOOL "Switch off CppUTest Test build")
FetchContent_MakeAvailable(CppUTest)

add_executable(run ${ENTRY_FILE} ${SRC_FILES})
add_executable(test ${SRC_FILES} ${TEST_FILES})

target_link_libraries(
    test PRIVATE
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)