# Compiler and linker
CXX = g++
INCDIR = include
CXXFLAGS = -Wall -Wextra -std=c++11 -O2 -I$(INCDIR)

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Target executable name
TARGET = $(BIN_DIR)/my_program

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

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

.PHONY: all clean compile link run

# # Compiler
# CXX = g++

# # Compiler flags
# CXXFLAGS = -g -Wall -Weffc++ -std=c++11 -Iinclude

# # Directories
# BIN_DIR = ./bin
# SRC_DIR = ./src

# # Source files
# SRC_FILES = $(SRC_DIR)/main.cpp \
#             $(SRC_DIR)/Beneficiary.cpp \
#             $(SRC_DIR)/Volunteer.cpp \
#             $(SRC_DIR)/SupplyRequest.cpp \
#             $(SRC_DIR)/MedicalWarehouse.cpp \
#             $(SRC_DIR)/Action.cpp

# # Object files
# OBJ_FILES = $(BIN_DIR)/main.o \
#             $(BIN_DIR)/Beneficiary.o \
#             $(BIN_DIR)/Volunteer.o \
#             $(BIN_DIR)/SupplyRequest.o \
#             $(BIN_DIR)/MedicalWarehouse.o \
#             $(BIN_DIR)/Action.o

# # Target executable
# TARGET = $(BIN_DIR)/executable

# all: clean compile link

# compile: $(OBJ_FILES)

# $(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<

# $(BIN_DIR):
# 	mkdir -p $(BIN_DIR)

# link: $(OBJ_FILES)
# 	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ_FILES)

# run: all
# 	$(TARGET)

# clean:
# 	rm -f $(BIN_DIR)/*

# .PHONY: all clean compile link run

