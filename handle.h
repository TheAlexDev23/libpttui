#ifndef _PTTUI_HANDLE_H_INCLUDE
#define _PTTUI_HANDLE_H_INCLUDE

#include <ncurses.h>

#include "ncurses.h"

struct _pttui_handle
{
    WINDOW* main_table;
    WINDOW* bottom_table;

    pttui_grid_element_t* elements[10 * 18];
};


#endif