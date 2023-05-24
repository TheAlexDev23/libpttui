#include <unistd.h>

#include "pttui.h"

#include "handle.h"
#include "init.h"
#include "exit.h"


int main()
{
    pttui_handle_t* handle = NULL;
    pttui_init(&handle);

    sleep(2);

    pttui_exit(handle);

    return 0;
}