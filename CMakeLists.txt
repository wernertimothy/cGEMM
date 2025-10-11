cmake_minimum_required(VERSION 3.15)
project(GEMMC)

include(CTest)
enable_testing(())

set(LIB_NAME GEMMC)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(${LIB_NAME} STATIC
    src/matrix.c
)

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(test)
add_subdirectory(examples)