# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Raylib library
RAYLIB_LIBS = -lraylib -ldl -lpthread -lm

# Directories
SRC_DIR = ./
LIB_DIR =../include
BUILD_DIR = build

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp $(wildcard $(LIB_DIR))/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Executable name
TARGET = skygift

# Default target
all: $(BUILD_DIR) $(TARGET)

# Rule to create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS) $(RAYLIB_LIBS)

# Rule to compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Phony target to clean up generated files
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
