# dmtksdl - da minimalist toolkit, sdl edition

Port of dmtk to SDL2. Currently unstable.  

## Usage

dmtksdl depends only on SDL (2.0.5 or later).

Copy the four headers files to your project, and include dmtk like this:

```
#define DMTK_IMPLEMENTATION
#include "dmtk.h"
```

Then, compile using these flags:

```
$ cc program.c -lm $(sdl2-config --cflags --libs) -o program
```

See the examples folder for basic usage.

