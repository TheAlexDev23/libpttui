#include <libperiodic-c/periodic.h>

#include "exit.h"

void pttui_exit(pttui_handle_t* handle)
{
    /* Free elements */
    for (int x = 0; x < 18; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            if (handle->elements[x][y]->element != NULL)
                periodic_free_element(handle->elements[x][y]->element);
        }
    }

    _pttui_ncurses_exit(handle);
}