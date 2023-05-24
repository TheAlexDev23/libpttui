cmake_minimum_required(VERSION 3.18.0)

project(pttui)

add_subdirectory(lib/libperiodic-c)

link_directories(lib/libperiodic-c/build)
include_directories(lib)

add_library(
    pttui
    pttui.h
    easy.h
    easy.c
    handle.h
    ncurses.h
    ncurses.c
)

target_link_libraries(pttui periodic-c)