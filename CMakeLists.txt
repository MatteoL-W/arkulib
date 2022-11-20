# Settings
cmake_minimum_required(VERSION 3.13)

set(LIB_NAME Arkulib)
project(${LIB_NAME} LANGUAGES C CXX)

# Get source & header files
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp)

# Find doxygen package (optional)
find_package(Doxygen OPTIONAL_COMPONENTS QUIET)
if(DOXYGEN_FOUND)
    add_subdirectory(docs)
else()
    message(WARNING "Doxygen is not found")
endif()

# Create the lib
add_library(${LIB_NAME} ${SRC_FILES} ${HEADER_FILES})

# Compilation settings
target_compile_features(${LIB_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -O2)

# Fetch Unit Tests
add_subdirectory(tests)

# Include directories
target_include_directories(${LIB_NAME} PRIVATE "include")


