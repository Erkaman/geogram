cmake_minimum_required(VERSION 3.10)

# Project name
project(LSCMExample)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define include directories

# src/lib/ -DNL_WITH_AMGCL -I src/lib/geogram/third_party/amgcl/  
#include_directories(include/ include/new/   )


# Define source files

file(GLOB MY_SOURCES_CPP src/*.cpp)
file(GLOB MY_SOURCES_C src/*.c)

# Create an executable    examples/geogram/opennl_LSCM/main.cpp
add_executable(${PROJECT_NAME}   ${MY_SOURCES_CPP} ${MY_SOURCES_C})

# Add a preprocessor definition
target_compile_definitions(${PROJECT_NAME} PRIVATE NL_WITH_AMGCL)
