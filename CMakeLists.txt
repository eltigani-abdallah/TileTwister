cmake_minimum_required(VERSION 3.20)

project(TileTwister VERSION 0.1.0 LANGUAGES CXX)

option(ENABLE_TESTS "Build tests" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- SDL2 (MSYS2 provides Config packages) ----
find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)

# ---- Core (no SDL) ----
add_library(tiletwister_core STATIC)

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

# ---- SDL layer (depends on core + SDL) ----
add_library(tiletwister_sdl STATIC)

target_sources(tiletwister_sdl
  PRIVATE
    src/GameObject.cpp
    src/GridView.cpp
    src/TileView.cpp
    src/Window.cpp
)

target_link_libraries(tiletwister_sdl
  PUBLIC
    tiletwister_core
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
)

# MSYS2 headers are usually in .../include/SDL2, so ensure it's visible
target_include_directories(tiletwister_sdl
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    /ucrt64/include/SDL2
)

# Important: prevent SDL from redefining main() on Windows/MinGW
target_compile_definitions(tiletwister_sdl PUBLIC SDL_MAIN_HANDLED)

# ---- Main game executable ----
add_executable(tiletwister
  src/main.cpp
)

target_compile_features(tiletwister PRIVATE cxx_std_20)

target_link_libraries(tiletwister
  PRIVATE
    tiletwister_sdl
)

# ---- SDL test executable ----
add_executable(sdl_test
  sdl/sdl_test.cpp
)

target_compile_features(sdl_test PRIVATE cxx_std_20)

target_link_libraries(sdl_test
  PRIVATE
    tiletwister_sdl
)

# ---- Tests (single runner) ----
if(ENABLE_TESTS)
  include(CTest)
  enable_testing()

  add_executable(tests_runner
    tests/test_main.cpp
    tests/TestGrid.cpp
    tests/TestMoves.cpp
  )
  target_compile_features(tests_runner PRIVATE cxx_std_20)
  target_link_libraries(tests_runner PRIVATE tiletwister_core)
  add_test(NAME tests_runner COMMAND tests_runner)

  if(WIN32)
    target_link_options(tests_runner PRIVATE -mconsole)
    set_target_properties(tests_runner PROPERTIES WIN32_EXECUTABLE OFF)
  endif()
endif()

# ---- Windows console + DLL copy ----
if(WIN32)
  # force console subsystem for these exes
  target_link_options(tiletwister PRIVATE -mconsole)
  target_link_options(sdl_test    PRIVATE -mconsole)

  # copy DLLs next to executables
  foreach(_tgt tiletwister sdl_test)
    add_custom_command(TARGET ${_tgt} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE:SDL2_ttf::SDL2_ttf>
        $<TARGET_FILE_DIR:${_tgt}>
    )
  endforeach()
endif()
