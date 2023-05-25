#include <stddef.h> // NULL

#include <libperiodic-c/periodic.h>

#include "easy.h"

#include "pttui.h"

#include "handle.h"
#include "init.h"
#include "exit.h"

periodic_element_t* pttui_easy_get_element(char* db_source)
{
    periodic_set_database(db_source);
    pttui_handle_t* handle = NULL;
    pttui_init(&handle);

    periodic_element_t* element = NULL;

    while (1)
    {
        if (_pttui_handle_input(handle))
        {
            pttui_grid_element_t* grid_element = _pttui_screen_point_to_grid_element(handle);
            if (grid_element != NULL)
                element = grid_element->element;
            
            break;
        }
    }

    pttui_exit(handle, element);

    return element;
}
