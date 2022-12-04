cmake_minimum_required(VERSION 3.13)

enable_testing()
set(EXECUTABLE_NAME Arkulib_tests)
add_executable(${EXECUTABLE_NAME})

# Get source files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "./*")
target_sources(${EXECUTABLE_NAME} PRIVATE ${SRC_FILES})

# Include Arkulib Library
include_directories(${CMAKE_SOURCE_DIR}/arkulib/include)
target_link_libraries(${EXECUTABLE_NAME} gtest Arkulib)

# Settings
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)

# Add Google Unit Tests
message(STATUS "Google Test CMake ...")
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
