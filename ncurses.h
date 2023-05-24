#ifndef _PTTUI_NCURSES_H_INCLUDED
#define _PTTUI_NCURSES_H_INCLUDED

#include <libperiodic-c/periodic.h>

#include "pttui.h"
#include "handle.h"

typedef struct _pttui_screen_point
{
    int x;
    int y;
} pttui_screen_point_t;

typedef struct _pttui_grid_element
{
    WINDOW* win;
    pttui_screen_point_t start;
    pttui_screen_point_t end;

    /* Accepted to be NULL for elements of grids that shouldn't have elements */
    periodic_element_t* element;
} pttui_grid_element_t ;

int _pttui_ncurses_init(pttui_handle_t* handle);
void _pttui_ncurses_exit(pttui_handle_t* handle);

void _pttui_ncurses_refresh(pttui_handle_t* handle);

#endif