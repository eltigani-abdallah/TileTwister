cmake_minimum_required(VERSION 3.20)
project(TileTwister LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_TESTS "Build tests" ON)

# ---- Core library ----
add_library(tiletwister_core
    src/core/Tile.cpp
    src/core/Grid.cpp
    src/core/Game.cpp
)

target_include_directories(tiletwister_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
)

if (MSVC)
    target_compile_options(tiletwister_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(tiletwister_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---- Terminal executable ----
add_executable(tiletwister
    src/main.cpp
)
target_link_libraries(tiletwister PRIVATE tiletwister_core)

# ---- Tests ----
if (ENABLE_TESTS)
    enable_testing()

    add_executable(test_grid src/tests/TestGrid.cpp)
    target_link_libraries(test_grid PRIVATE tiletwister_core)
    add_test(NAME test_grid COMMAND test_grid)

    add_executable(test_moves src/tests/TestMoves.cpp)
    target_link_libraries(test_moves PRIVATE tiletwister_core)
    add_test(NAME test_moves COMMAND test_moves)
endif()


# SDL2 from MSYS2 provides SDL2Config.cmake -> use CONFIG
find_package(SDL2 REQUIRED CONFIG)

add_executable(sdl_test sc/sdl/sdl_test.cpp)

target_link_libraries(sdl_test PRIVATE SDL2::SDL2main SDL2::SDL2)

if (WIN32)
    add_custom_command(TARGET sdl_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2::SDL2>
            $<TARGET_FILE_DIR:sdl_test>
    )
endif()
