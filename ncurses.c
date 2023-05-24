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

/*
* Draws a box in the grid at x and y
* Note that x, y are grid coordintates and not scren coordinates
* Refreshes win
*/
void draw_box(WINDOW* win, int x, int y)
{
    int startx = x * 5;
    int starty = y * 5;
    int endx = (x + 1) * 5 - 1;
    int endy = (y + 1) * 5 - 1;

    mvwhline(win, starty, startx, 0, endx - startx);
    mvwhline(win, endy, startx, 0, endx - startx);
    mvwvline(win, starty, startx, 0, endy - starty);
    mvwvline(win, starty, endx, 0, endy - starty);
    mvwaddch(win, starty, startx, ACS_ULCORNER);
    mvwaddch(win, endy, startx, ACS_LLCORNER);
    mvwaddch(win, starty, endx, ACS_URCORNER);
    mvwaddch(win, endy, endx, ACS_LRCORNER);

    wrefresh(win);
}

void _pttui_ncurses_refresh(pttui_handle_t* handle)
{
    /* Draw grid */
    for (int x = 0; x < 18; x++)
    {
        for (int y = 0; y < 7; y++)
        {
            if (handle->elements[x][y].element == NULL)
            {
                continue;
            }

            draw_box(handle->main_table, x, y);
            mvwprintw(handle->main_table, y * 5 + 2, x * 5 + 1, handle->elements[x][y].element->symbol);
            handle->elements[x][y].win = handle->main_table;

            handle->elements[x][y].start.x = x * 5;
            handle->elements[x][y].start.y = y * 5;

            handle->elements[x][y].end.x = (x + 1) * 5;
            handle->elements[x][y].end.y = (y + 1) * 5;
        }

        for (int y = 8; y < 10; y++)
        {
            if (handle->elements[x][y].element == NULL)
            {
                continue;
            }
            draw_box(handle->bottom_table, x, y);
            mvwprintw(handle->bottom_table, y * 5 + 2, x * 5 + 1, handle->elements[x][y].element->symbol);
            handle->elements[x][y].win = handle->bottom_table;

            handle->elements[x][y].start.x = x * 5;
            handle->elements[x][y].start.y = y * 5;

            handle->elements[x][y].end.x = (x + 1) * 5;
            handle->elements[x][y].end.y = (y + 1) * 5;
        }
    }
}

int _pttui_ncurses_init(pttui_handle_t* handle)
{
    initscr();

    raw();
    noecho();

    if (check_screen_size())
    {
        _pttui_ncurses_exit(handle);
        return -1;
    }

    handle->main_table = newwin(5 * 7, 5 * 18, 0, 0);
    handle->bottom_table = newwin(5 * 2, 5 * 18, 8 * 5, 0);

    _pttui_ncurses_refresh(handle);

    return 0;
}

void _pttui_ncurses_exit(pttui_handle_t* handle)
{
    endwin();
}
