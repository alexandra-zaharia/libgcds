# libgcds tests

Supposing you cloned this git repository, simply run the provided `makefile` to compile the tests. 

Run the tests with `make run`. 

Remove the tests with `make clean`.

## Testing framework

The tests use the [cmocka](https://cmocka.org) framework (it therefore needs to be installed on your system to run the tests). 

## Tested library build

The `makefile` will build the tests using the static library in [../build/lib](https://github.com/alexandra-zaharia/libgcds/tree/master/build/lib) and the header files in [../build/include](https://github.com/alexandra-zaharia/libgcds/tree/master/build/include). You may change this through the `LIB` and `INC` variables, respectively, in the `makefile`.
