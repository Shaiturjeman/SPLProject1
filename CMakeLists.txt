cmake_minimum_required(VERSION 3.12)

project(MyProject)

# Add your project configuration and dependencies here
set(SOURCES src/main.cpp src/foo.cpp)
add_executable(MyExecutable ${SOURCES})
target_link_libraries(MyExecutable MyLibrary)

# Add your source files and targets here
set(SRC_DIR /workspaces/SPLProject1/Skeleton/Skeleton/src)
set(OBJ_DIR /workspaces/SPLProject1/Skeleton/Skeleton/obj)
set(BIN_DIR /workspaces/SPLProject1/Skeleton/Skeleton/bin)

set(SRC_FILES 
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Beneficiary.cpp
    ${SRC_DIR}/Volunteer.cpp
    ${SRC_DIR}/SupplyRequest.cpp
    ${SRC_DIR}/MedicalWarehouse.cpp
    ${SRC_DIR}/Action.cpp
)

# In CMake, you don't need to manually specify the object files.
# CMake will handle this for you when you add an executable or library.

# Add the executable
add_executable(my_program ${SRC_FILES})

# Specify the output directory for the executable
set_target_properties(my_program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)