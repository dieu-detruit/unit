cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_FLAG "${CMAKE_C_FLAGS} -g -O0 -fmax-errors=5 -Wfatal-erros")
set(CMAKE_CXX_FLAG "${CMAKE_C_FLAGS} -g -O0 -fmax-errors=5 -Wfatal-erros -std=c++2a")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(UNIT LANGUAGES C CXX)

# add test executables
file(GLOB TEST_SOURCES testsuite/*.cpp)
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_include_directories(${TEST_NAME} PRIVATE include)
endforeach()
