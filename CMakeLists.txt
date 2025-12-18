cmake_minimum_required(VERSION 3.20)
project(TileTwister LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_TESTS "Build tests" ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# -------------------------
# Core library (testable)
# -------------------------
add_library(TileTwisterLib STATIC
    src/GameManager.cpp
        src/InputManager.cpp
        src/sdl/Window.cpp
)

target_include_directories(TileTwisterLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (MSVC)
    target_compile_options(TileTwisterLib PRIVATE /W4 /permissive-)
else()
    target_compile_options(TileTwisterLib PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(TileTwisterLib PUBLIC SDL3::SDL3)

# -------------------------
# Main executable
# -------------------------
add_executable(TileTwister
    src/main.cpp
)

target_link_libraries(TileTwister PRIVATE TileTwisterLib)

if (WIN32)
    add_custom_command(TARGET TileTwister POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE_DIR:TileTwister>
    )
endif()

# -------------------------
# Tests
# -------------------------
if(ENABLE_TESTS)
    include(CTest)
    enable_testing()

    add_executable(test_grid tests/TestGrid.cpp)
    target_compile_features(test_grid PRIVATE cxx_std_20)
    target_link_libraries(test_grid PRIVATE TileTwisterLib)
    add_test(NAME test_grid COMMAND test_grid)

    add_executable(test_moves tests/TestMoves.cpp)
    target_compile_features(test_moves PRIVATE cxx_std_20)
    target_link_libraries(test_moves PRIVATE TileTwisterLib)
    add_test(NAME test_moves COMMAND test_moves)
endif()
