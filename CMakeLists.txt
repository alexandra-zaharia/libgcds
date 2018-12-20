cmake_minimum_required(VERSION 3.10)
project(gcdslib)

set(CMAKE_C_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-g -Wall -Wextra -Wpedantic -Wconversion")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(
        include
        include/LinkedList
        include/Queue
        include/Stack
        include/Vector
)

add_library(gcds STATIC
        src/node.c
        src/LinkedList/linked_list.c
        src/Queue/queue.c
        src/Stack/stack.c
        src/Vector/vector.c)

install(TARGETS gcds DESTINATION lib)
install(FILES
        include/node.h
        include/LinkedList/linked_list.h
        include/Queue/queue.h
        include/Stack/stack.h
        include/Vector/vector.h
        DESTINATION include)