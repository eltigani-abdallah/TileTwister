cmake_minimum_required(VERSION 3.20)
project(TileTwister LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Options (later) ----
option(ENABLE_TESTS "Build unit tests" ON)

# ---- Core library ----
# add_library(tiletwister_core
#     src/core/Grid.cpp
#     src/core/Game.cpp
# )

# target_include_directories(tiletwister_core PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/core
# )

# Warnings (GCC/Clang/MSVC)
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

# ---- Tests placeholder (optional) ----
if (ENABLE_TESTS)
    enable_testing()
    # You can add Catch2/GoogleTest later.
    # add_executable(tests tests/test_moves.cpp ...)
    # target_link_libraries(tests PRIVATE tiletwister_core)
    # add_test(NAME tiletwister_tests COMMAND tests)
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
