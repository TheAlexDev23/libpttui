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

    while (!_pttui_handle_input(handle))
    {
        element = _pttui_screen_point_to_grid_element(handle).element;
    }

    pttui_exit(handle, element);

    return element;
}
