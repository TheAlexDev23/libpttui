#include <ncurses.h>
#include <stdlib.h>

#include "pttui.h"
#include "handle.h"
#include "ncurses.h"

/* 
* Returns -1 if screen size is not big enough for a periodic table
* Uses stdscr's size
*/
int check_screen_size()
{
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    /* Width is 18 groups * 5 characters per group */
    if ((float)maxX / 5.0 < 18)
        return -1;

    /* Height is (7 rows + 1 row of space + 2 rows) * 5 characters per row */
    if ((float)maxY / 5.0 < 10)
        return -1;

    return 0;
}

int pttui_ncurses_init(pttui_handle_t** handle)
{
    *handle = calloc(sizeof(pttui_handle_t), 1);

    initscr();

    if (check_screen_size())
    {
        pttui_ncurses_exit(*handle);
        return -1;
    }

    return 0;
}

int pttui_ncurses_exit(pttui_handle_t* handle)
{

}