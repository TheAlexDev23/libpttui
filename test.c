#include <stdio.h>

#include <libperiodic-c/periodic.h>

#include "easy.h"

int main()
{
    periodic_element_t* element = pttui_easy_get_element("./lib/libperiodic-c/Periodic-Table-JSON/PeriodicTableJSON.json");
    printf("%s", element->name);

    return 0;
}