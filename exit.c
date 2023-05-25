#include <stdlib.h>

#include <libperiodic-c/periodic.h>

#include "exit.h"

void pttui_exit(pttui_handle_t* handle, periodic_element_t* selected_element)
{
    _pttui_ncurses_exit(handle);
    
    /* Free elements */
    for (int x = 0; x < 18; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            periodic_element_t* element = handle->elements[x][y].element;
            if (element != NULL)
            {
                if (selected_element != NULL && selected_element->number == element->number)
                   continue;

                periodic_free_element(element);
            }
        }
    }

    free(handle);
}