# Settings
cmake_minimum_required(VERSION 3.13)

set(LIB_NAME Arkulib)
project(${LIB_NAME} LANGUAGES C CXX)

# Get source & header files
file(GLOB_RECURSE HEADER_FILES include/*.hpp)

# Create the lib
add_library(${LIB_NAME} INTERFACE ${HEADER_FILES})

# Find doxygen package (optional)
find_package(Doxygen OPTIONAL_COMPONENTS QUIET)
if(DOXYGEN_FOUND)
    add_subdirectory(docs)
else()
    message(WARNING "Doxygen is not found")
endif()


# Fetch Unit Tests
add_subdirectory(tests)


