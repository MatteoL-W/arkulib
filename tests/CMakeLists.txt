cmake_minimum_required(VERSION 3.13)

enable_testing()
add_executable(arkulib_tests cosine.cpp Sqrt.cpp)

# Get source files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "./*")

# Link files to project target
target_sources(arkulib_tests PRIVATE ${SRC_FILES})
target_link_libraries(arkulib_tests gtest Arkulib)
target_compile_features(arkulib_tests PRIVATE cxx_std_17)

# Add Google Unit Tests
message(STATUS "Google Test CMake ..." )
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
