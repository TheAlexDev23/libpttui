#include <unistd.h>

#include <libperiodic-c/periodic.h>

#include "pttui.h"

#include "handle.h"
#include "init.h"
#include "exit.h"


int main()
{
    periodic_set_database("./lib/libperiodic-c/Periodic-Table-JSON/PeriodicTableJSON.json");
    pttui_handle_t* handle = NULL;
    pttui_init(&handle);

    sleep(2);

    //pttui_exit(handle);

    return 0;
}