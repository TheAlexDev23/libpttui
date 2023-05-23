cmake_minimum_required(VERSION 3.18.0)

project(pttui)

add_subdirectory(lib/libperiodic-c)

add_library(
    ${project_name}
    pttui.h
    easy.h
    easy.c
    ncurses.h
    ncurses.c
)
