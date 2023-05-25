# Periodic Table TUI

C library with an easy to use API for choosing elements of the periodic table. Calling the API will return an element selected by the user in the TUI interface.

Uses ncurses and [libperiodic-c](https://github.com/thealexdev23/libperiodic-c).

Is part of multiple projects I made for a school project. But it still an be used on itself.

## API

```C
#include <libperiodic-c/periodic.h>

#include <libpttui/easy.h>

int main()
{
    ...

    periodic_element_t* element = pttui_easy_get_element("path to elements json database");

    ...
}
```

For a more detailed example refer to [test.c](test.c)