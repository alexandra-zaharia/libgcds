# libgcds tests

Supposing you cloned this git repository, simply run the provided `makefile` to compile the tests. 

Run the tests with `make run`. 

Remove the tests with `make clean`.

## Testing framework

The tests use the [cmocka](https://cmocka.org) framework (it therefore needs to be installed on your system to run the tests). 

## Tested library build

The `makefile` will build the tests using the static library in [../build/lib](https://github.com/alexandra-zaharia/libgcds/tree/master/build/lib) and the header files in [../build/include](https://github.com/alexandra-zaharia/libgcds/tree/master/build/include). You may change this through the `LIB` and `INC` variables, respectively, in the `makefile`.

## -Wconversion warnings

There are some `-Wsign-conversion` warnings when compiling the tests. This is due to the fact that the number of items in a data structure is stored as an `unsigned int`. When the user attempts to insert or remove an item at an invalid (negative) index, this generates a compiler warning. The data structures themselves handle such situations gracefully: the index (which should be an unsigned integer) is first converted to an integer and checked whether this integer it is negative, in which case the returns an failure code. 