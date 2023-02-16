cmake_minimum_required(VERSION 3.0)
project(SimpleTraycing)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(CPP "${CMAKE_CURRENT_LIST_DIR}/src")
set(HPP "${CMAKE_CURRENT_LIST_DIR}/include")

FILE(GLOB CPP_FILE ${CPP}/*.cxx)
FILE(GLOB HPP_FILE ${HPP}/*.hxx)

set(MAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/src/10_PositionableCamera_2.cpp")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_compile_options(-Wall -Werror)

add_executable(${PROJECT_NAME} ${MAIN_FILE} ${CPP_FILE} ${HPP_FILE})
