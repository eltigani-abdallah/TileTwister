cmake_minimum_required(VERSION 3.20)

project(TileTwister VERSION 0.1.0 LANGUAGES CXX)

option(ENABLE_TESTS "Build tests" ON)

# Utile pour clangd/IDE
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Core library ----
add_library(tiletwister_core)

target_sources(tiletwister_core
    PRIVATE
        src/Direction.cpp
        src/Tile.cpp
        src/Grid.cpp
        src/Game.cpp
)

target_include_directories(tiletwister_core
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_compile_features(tiletwister_core PUBLIC cxx_std_20)

target_compile_options(tiletwister_core
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

# ---- Main executable ----
add_executable(tiletwister
    src/main.cpp
)
target_compile_features(tiletwister PRIVATE cxx_std_20)
target_link_libraries(tiletwister PRIVATE tiletwister_core)

# ---- Tests ----
if(ENABLE_TESTS)
    include(CTest)
    enable_testing()

    add_executable(test_grid tests/TestGrid.cpp)
    target_compile_features(test_grid PRIVATE cxx_std_20)
    target_link_libraries(test_grid PRIVATE tiletwister_core)
    add_test(NAME test_grid COMMAND test_grid)

    add_executable(test_moves tests/TestMoves.cpp)
    target_compile_features(test_moves PRIVATE cxx_std_20)
    target_link_libraries(test_moves PRIVATE tiletwister_core)
    add_test(NAME test_moves COMMAND test_moves)
endif()

# ---- SDL2 ----
# SDL2 from MSYS2 provides SDL2Config.cmake -> use CONFIG
find_package(SDL2 REQUIRED CONFIG)

# IMPORTANT: adapte le chemin si ton fichier n'est pas à cet endroit
add_executable(sdl_test
    sdl/sdl_test.cpp
)

target_compile_features(sdl_test PRIVATE cxx_std_20)

target_link_libraries(sdl_test
    PRIVATE
        SDL2::SDL2main
        SDL2::SDL2
)

# Copie automatique de la DLL SDL2 à côté de l'exe sur Windows
if(WIN32)
    add_custom_command(TARGET sdl_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2::SDL2>
            $<TARGET_FILE_DIR:sdl_test>
    )
endif()
