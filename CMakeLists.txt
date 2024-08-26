cmake_minimum_required(VERSION 3.10)

# Project name
project(LSCMExample)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source files

file(GLOB MY_SOURCES_CPP src/*.cpp)
file(GLOB MY_SOURCES_C src/*.c)

add_library(mylib ${MY_SOURCES_CPP} ${MY_SOURCES_C})
target_compile_definitions(mylib PRIVATE NL_WITH_AMGCL)
 
add_executable(myexe   examples/geogram/opennl_LSCM/main.cpp )

target_link_libraries(myexe mylib)

#target_compile_definitions(myexe PRIVATE NL_WITH_AMGCL)

target_include_directories(myexe PUBLIC src/)
