#include <libperiodic-c/periodic.h>

#include "init.h"

#include "ncurses.h"

int pttui_init(pttui_handle_t** handle)
{
    *handle = calloc(sizeof(pttui_handle_t), 1);

    periodic_element_t** elements = periodic_get_all_elements();

    for (int i = 0; i < 128; i++)
    {
        periodic_element_t* element = elements[i];
        int x = element->pos.posX;
        int y = element->pos.posY;
        (*handle)->elements[x][y]->element = element;
    }

    if (_pttui_ncurses_init(*handle))
    {
        periodic_free_elements(elements);
        return -1;
    }

    return 0;
}