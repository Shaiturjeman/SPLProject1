cmake_minimum_required(VERSION 3.12)

project(MyProject)


# Add your project configuration and dependencies here
set(SOURCES src/main.cpp src/foo.cpp)
add_executable(MyExecutable ${SOURCES})
target_link_libraries(MyExecutable MyLibrary)

# Add your source files and targets here
SRC_DIR = /workspaces/SPLProject1/Skeleton/Skeleton/src
OBJ_DIR = /workspaces/SPLProject1/Skeleton/Skeleton/obj
BIN_DIR = /workspaces/SPLProject1/Skeleton/Skeleton/bin

SRC_FILES = $(SRC_DIR)/main.cpp \
			$(SRC_DIR)/Beneficiary.cpp \
			$(SRC_DIR)/Volunteer.cpp \
			$(SRC_DIR)/SupplyRequest.cpp \
			$(SRC_DIR)/MedicalWarehouse.cpp \
			$(SRC_DIR)/Action.cpp

OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

TARGET = $(BIN_DIR)/my_program