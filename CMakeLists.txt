cmake_minimum_required(VERSION 3.10)

# Project name
project(LSCMExample)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define include directories

# src/lib/ -DNL_WITH_AMGCL -I src/lib/geogram/third_party/amgcl/  
include_directories(include/ include/new/  include/geogram/third_party/amgcl/  )

# Define source files

file(GLOB MY_SOURCES_CPP src/*.cpp)
file(GLOB MY_SOURCES_C src/*.c)

file(GLOB BASIC_SOURCES src/geogram/basic/*.cpp)

file(GLOB DEL_SRC src/geogram/delaunay/*.cpp)

file(GLOB IMG_SRC src/geogram/image/*.cpp)

file(GLOB MESH_SRC src/geogram/mesh/*.cpp)

file(GLOB NUM_SRC src/geogram/numerics/*.cpp)

file(GLOB PARAM_SRC src/geogram/parameterization/*.cpp)

file(GLOB NL_SRC src/geogram/NL/*.c)

file(GLOB NL_SRC_CPP src/geogram/NL/*.cpp)

file(GLOB POINTS_SRC src/geogram/points/*.cpp)

file(GLOB VORONOI_SRC src/geogram/voronoi/*.cpp)

file(GLOB BIB_SRC src//geogram/bibliography/*.cpp)



file(GLOB XATLAS_SRC src/geogram/third_party/xatlas/*.cpp)

# Create an executable
add_executable(${PROJECT_NAME} examples/geogram/opennl_LSCM/main.cpp ${BASIC_SOURCES} ${DEL_SRC} ${IMG_SRC} ${MESH_SRC} ${NUM_SRC} ${PARAM_SRC} ${NL_SRC} ${NL_SRC_CPP} ${POINTS_SRC} ${VORONOI_SRC} ${XATLAS_SRC} ${BIB_SRC} ${MY_SOURCES_CPP} ${MY_SOURCES_C})

# Add a preprocessor definition
target_compile_definitions(${PROJECT_NAME} PRIVATE NL_WITH_AMGCL)
