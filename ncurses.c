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

/* 
* Draws box and name of element in the needed grid element. 
* Window of element needs to be set before calling 
*/
void refresh_element(pttui_grid_element_t* element, int x, int y)
{
    if (element->element == NULL)
        return;

    draw_box(element->win, x, y);
    mvwprintw(element->win, y * 5 + 2, x * 5 + 1, element->element->symbol);

    wrefresh(element->win);

    element->start.x = x * 5;
    element->start.y = y * 5;

    element->end.x = (x + 1) * 5;
    element->end.y = (y + 1) * 5;
}

void _pttui_ncurses_refresh(pttui_handle_t* handle)
{
    /* Draw grid */
    for (int x = 0; x < 18; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            handle->elements[x][y].win = handle->main_table;
            refresh_element(&(handle->elements[x][y]), x, y);
        }
    }
}

pttui_grid_element_t* _pttui_screen_point_to_grid_element(pttui_handle_t* handle)
{
    int cury = getcury(handle->main_table);
    int curx = getcurx(handle->main_table);

    for (int x = 0; x < 18; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            /* Basically a way of checking if grid element isn't part of the peridic table */
            if (handle->elements[x][y].element == NULL)
                continue;
            
            pttui_grid_element_t element = handle->elements[x][y];

            fprintf(stderr, "%i %i %i %i\n", curx, cury, element.start.x, element.start.y);

            if (curx > element.start.x && curx < element.end.x &&
                cury > element.start.y && cury < element.end.y)
            {
                return &(handle->elements[x][y]);
            }
        }
    }

    return NULL;
}

bool _pttui_handle_input(pttui_handle_t* handle)
{
    restart:;
    int ch = wgetch(handle->main_table);

    int x = getcurx(handle->main_table);
    int y = getcury(handle->main_table);

    switch (ch)
    {
        case KEY_UP:
            if (y <= 0)
                break;
            wmove(handle->main_table, y - 1, x);
            break;
        case KEY_DOWN:
            if (y >= getmaxy(handle->main_table))
                break;
            wmove(handle->main_table, y + 1, x);
            break;
        case KEY_LEFT:
            if (x <= 0)
                break;
            wmove(handle->main_table, y, x - 1);
            break;
        case KEY_RIGHT:
            if (x >= getmaxx(handle->main_table))
                break;
            wmove(handle->main_table, y, x + 1);
            break;
        case '\n':
            return true;
            break;
        default:
            goto restart;
    }

    return false;
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
    handle->main_table = newwin(5 * 10, 5 * 18, 0, 0);
    keypad(handle->main_table, TRUE);

    _pttui_ncurses_refresh(handle);

    return 0;
}

void _pttui_ncurses_exit(pttui_handle_t* handle)
{
    endwin();
}
