cmake_minimum_required(VERSION 3.20)
project(TileTwister LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
