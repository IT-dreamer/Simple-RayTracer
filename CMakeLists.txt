cmake_minimum_required(VERSION 3.0)
project(SimpleTraycing)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(CPP "${CMAKE_CURRENT_LIST_DIR}/src")
set(HPP "${CMAKE_CURRENT_LIST_DIR}/include")

FILE(GLOB CPP_FILE ${CPP}/*.cxx)
FILE(GLOB HPP_FILE ${HPP}/*.hxx)

set(MAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/src/7_DiffuseMaterial.cpp")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_compile_options(-Wall -Werror)

add_executable(${PROJECT_NAME} ${MAIN_FILE} ${CPP_FILE} ${HPP_FILE})