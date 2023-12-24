CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Raylib library
RAYLIB_LIBS = -lraylib -ldl -lpthread -lm
# Source files and executable name
SRCS = main.cpp
TARGET = snake

# Build rule
$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET) $(CXXFLAGS) $(RAYLIB_LIBS) 

# Phony target to clean up generated files
.PHONY: clean
clean:
	rm -f $(TARGET)
