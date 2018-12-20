# libgcds

**Lib**rary for **G**eneric **C D**ata **S**tructures

## Data structures 

For the moment, `libgcds` features the following data structures:
  * [`LinkedList`](https://github.com/alexandra-zaharia/libgcds/blob/master/docs/LinkedList.md) -- A doubly linked list implementation accepting insertion and removal operations at the beginning, at the end, or at a specified index in the linked list.
  * [`Queue`](https://github.com/alexandra-zaharia/libgcds/blob/master/docs/Queue.md) -- A queue implementation accepting `enqueue` and `dequeue` operations.
  * [`Stack`](https://github.com/alexandra-zaharia/libgcds/blob/master/docs/Stack.md) -- A stack implementation accepting `push` and `pop` operations.
  * [`Vector`](https://github.com/alexandra-zaharia/libgcds/blob/master/docs/Vector.md) -- A vector implementation using an underlying resizing array.
  
More data structures will be added in the future.

## API

The **API** of each data structure is detailed in the [documentation](https://github.com/alexandra-zaharia/libgcds/tree/master/docs).

The **TL;DR** API for a hypothetical `DataStructure` containing elements of type `Item` is as follows:

```c
DataStructure* ds = data_structure_create(); // NULL if error
int status = ds->some_add_operation(ds, &item); // 0 for success
Item* item = (Item*) ds->some_remove_operation(ds); // NULL if error
ds->free(ds);
``` 

## Examples

Usage examples for each data structure are provided in the [examples](https://github.com/alexandra-zaharia/libgcds/tree/master/examples) directory.

## How to install the library

You will need `cmake` and `make` to build a static `libgcds.a` library that can be used in your projects. 

First, clone the `libgcds` repository:

```bash
git clone https://github.com/alexandra-zaharia/libgcds.git
``` 

Then, create a build directory for CMake and `cd` into it:

```bash
cd libgcds
mkdir build
cd build
```

Next, run `cmake` to generate a `makefile`:

```bash
cmake .. -DCMAKE_INSTALL_PREFIX=/path/to/libgcds/install/dir
```

You may omit the `-DCMAKE_INSTALL_PREFIX` flag, in which case `libgcds` will be installed to a standard location such as `/usr/local`. Finally, make and install the library:

```bash
make && make install
```

This results in copying the library's header files in the `include/` subdirectory in your `CMAKE_INSTALL_PREFIX` (or `/usr/local` if an install prefix was not specified), and in copying the static library `libgcds.a` in the `lib/` subdirectory in the `CMAKE_INSTALL_PREFIX`.

## How to use the library

Simply include the required header files for your project, e.g. `#include "stack.h"` if you plan on using a `Stack`. For detailed information on the API of each data structure in `libgcds`, see the [documentation](https://github.com/alexandra-zaharia/libgcds/tree/master/docs).

When compiling a program that uses `libgcds` you will need to:
  * specify where the header files are located (`-I` for gcc)
  * specify the library search path (`-L` for `gcc`)
  * specify `gcds`, the library the linker needs to link with (`-l` for `gcc`)

Example:

```bash
gcc -o main main.c -I /path/to/libgcds/install/dir/include -L /path/to/libgcds/install/dir/lib -lgcds
```

## Tests

Tests for each data structure are provided in the [tests](https://github.com/alexandra-zaharia/libgcds/tree/master/tests) directory. They need to be linked with [cmocka](https://cmocka.org).
