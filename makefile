# Compiler and linker
CXX = g++
INCDIR = /workspaces/SPLProject1/Skeleton/Skeleton/include
CXXFLAGS = -Wall -Wextra -std=c++11 -O2 -I$(INCDIR) -g

# Directories
SRC_DIR = /workspaces/SPLProject1/Skeleton/Skeleton/src
OBJ_DIR = /workspaces/SPLProject1/Skeleton/Skeleton/obj
BIN_DIR = /workspaces/SPLProject1/Skeleton/Skeleton/bin

# Target executable name
TARGET = $(BIN_DIR)/my_program

# Source and object files
SRC_FILES = $(SRC_DIR)/main.cpp \
			$(SRC_DIR)/Beneficiary.cpp \
			$(SRC_DIR)/Volunteer.cpp \
			$(SRC_DIR)/SupplyRequest.cpp \
			$(SRC_DIR)/MedicalWarehouse.cpp \
			$(SRC_DIR)/Action.cpp

OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Default target
all: $(TARGET) run

# Linking the target executable
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES) -o $(TARGET)

print-src-dir:
	@echo "Contents of $(SRC_DIR):"
	@ls $(SRC_DIR)	

# Compiling source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# New rule to run the program
run:
	$(TARGET)

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) 

# Rebuild target
rebuild: clean all

.PHONY: all clean compile link run

