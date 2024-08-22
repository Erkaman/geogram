cmake_minimum_required(VERSION 3.10)

# Project name
project(LSCMExample)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define include directories

# src/lib/ -DNL_WITH_AMGCL -I src/lib/geogram/third_party/amgcl/  
include_directories(src/lib/ src/lib/geogram/third_party/amgcl/  )

# Define source files

file(GLOB BASIC_SOURCES src/lib/geogram/basic/*.cpp)

file(GLOB DEL_SRC src/lib/geogram/delaunay/*.cpp)

file(GLOB IMG_SRC src/lib/geogram/image/*.cpp)

file(GLOB MESH_SRC src/lib/geogram/mesh/*.cpp)

file(GLOB NUM_SRC src/lib/geogram/numerics/*.cpp)

file(GLOB PARAM_SRC src/lib/geogram/parameterization/*.cpp)

file(GLOB NL_SRC src/lib/geogram/NL/*.c)

file(GLOB NL_SRC_CPP src/lib/geogram/NL/*.cpp)

file(GLOB POINTS_SRC src/lib/geogram/points/*.cpp)

file(GLOB VORONOI_SRC src/lib/geogram/voronoi/*.cpp)

file(GLOB BIB_SRC src/lib/geogram/bibliography/*.cpp)



file(GLOB XATLAS_SRC src/lib/geogram/third_party/xatlas/*.cpp)

# Create an executable
add_executable(${PROJECT_NAME} src/examples/geogram/opennl_LSCM/main.cpp ${BASIC_SOURCES} ${DEL_SRC} ${IMG_SRC} ${MESH_SRC} ${NUM_SRC} ${PARAM_SRC} ${NL_SRC} ${NL_SRC_CPP} ${POINTS_SRC} ${VORONOI_SRC} ${XATLAS_SRC} ${BIB_SRC} )

# Add a preprocessor definition
target_compile_definitions(${PROJECT_NAME} PRIVATE NL_WITH_AMGCL)
