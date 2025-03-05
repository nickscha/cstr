# cstr
A C89 standard compliant, single header, nostdlib (no C Standard Library) string library.

For more information please look at the "cstr.h" file or take a look at the "examples" or "tests" folder.

## Quick Start

Download or clone cstr.h and include it in your project.

```C
#include "cstr.h"

int main() {

    return 0;
}
```

## Run Example: nostdlib, freestsanding

In this repo you will find the "examples/cstr_win32_nostdlib.c" with the corresponding "build.bat" file which
creates an executable only linked to "kernel32" and "user32" and is not using the C standard library and executes the program afterwards.
