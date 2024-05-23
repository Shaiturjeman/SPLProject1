# Compiler and linker
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2 -I$(INCDIR)

# Directories
SRC_DIR = Skeleton/src
OBJ_DIR = Skeleton/obj
BIN_DIR = Skeleton/bin

# Target executable name
TARGET = $(BIN_DIR)/my_program

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
INCDIR = Skeleton/include

# Default target
all: $(TARGET)

# Linking the target executable
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES) -o $(TARGET)

# Compiling source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Rebuild target
rebuild: clean all

.PHONY: all clean rebuild
