#ifndef _PTTUI_NCURSES_H_INCLUDED
#define _PTTUI_NCURSES_H_INCLUDED

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

    /* Accepted to be NULL for grids that don't have elements */
    periodic_element_t* element;
} pttui_grid_element_t ;

int pttui_ncurses_init();
int pttui_ncurses_exit();

#endif