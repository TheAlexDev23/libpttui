#ifndef _PTTUI_EXIT_H_INCLUDED
#define _PTTUI_EXIT_H_INCLUDED

#include "pttui.h"
#include "handle.h"

/* Exits and frees all elements handle references except for selected_element */
void pttui_exit(pttui_handle_t* handle, periodic_element_t* selected_element);

#endif