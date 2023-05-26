cmake_minimum_required(VERSION 3.18.0)

project(pttui)

add_subdirectory(lib/libperiodic-c)

link_directories(lib/libperiodic-c/build)

add_library(
    pttui
    pttui.h
    easy.h
    easy.c
    init.h
    init.c
    exit.h
    exit.c
    handle.h
    ncurses.h
    ncurses.c
)

target_include_directories(${PROJECT_NAME} PUBLIC lib)

target_link_libraries(pttui periodic-c ncurses)