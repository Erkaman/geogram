# Compiler
CXX = clang++ 
CXXFLAGS = -Wall -Wextra -std=c++17 -I src/lib/ -DNL_WITH_AMGCL -I src/lib/geogram/third_party/amgcl/   

# Source files
SRC_DIR = src
EXAMPLE_SRC = $(SRC_DIR)/examples/geogram/opennl_LSCM/main.cpp


BASIC_SRC = $(wildcard $(SRC_DIR)/lib/geogram/basic/*.cpp)

BIB_SRC = $(wildcard $(SRC_DIR)/lib/geogram/bibliography/*.cpp)
DEL_SRC = $(wildcard $(SRC_DIR)/lib/geogram/delaunay/*.cpp)
IMG_SRC = $(wildcard $(SRC_DIR)/lib/geogram/image/*.cpp)
MESH_SRC = $(wildcard $(SRC_DIR)/lib/geogram/mesh/*.cpp)
NL_SRC = $(wildcard $(SRC_DIR)/lib/geogram/NL/*.c)
NUM_SRC = $(wildcard $(SRC_DIR)/lib/geogram/numerics/*.cpp)
PARAM_SRC = $(wildcard $(SRC_DIR)/lib/geogram/parameterization/*.cpp)
POINTS_SRC = $(wildcard $(SRC_DIR)/lib/geogram/points/*.cpp)
VOR_SRC = $(wildcard $(SRC_DIR)/lib/geogram/voronoi/*.cpp)
MESH_SRC = $(wildcard $(SRC_DIR)/lib/geogram/mesh/*.cpp)


SRCS = $(EXAMPLE_SRC) $(BASIC_SRC) $(BIB_SRC) $(DEL_SRC) $(IMG_SRC) $(MESH_SRC) $(NL_SRC) $(NUM_SRC) $(PARAM_SRC) $(POINTS_SRC) $(VOR_SRC) $(MESH_SRC)

# Object files
OBJS = $(SRCS:.cpp=.o) $(SRCS:.c=.o)

# Executable
TARGET = lscm_example

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

# Compiling
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
