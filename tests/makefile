CC=gcc
CFLAGS=-g -Wall -Wextra -Wpedantic -Wconversion 

# INC specifies where libgcds header files are located
INC=-I../bin/include

# LIB specifies where the static library libgcds.a is located
LIB=-L ../bin/lib

# Tell the linker to link with libgcds and libcmocka
LDFLAGS=-lgcds -lcmocka

all: circular_linked_list-test linked_list-test queue-test stack-test vector-test

circular_linked_list-test: circular_linked_list-test.c
	$(CC) $< $(CFLAGS) $(INC) $(LIB) $(LDFLAGS) -o $@

linked_list-test: linked_list-test.c
	$(CC) $< $(CFLAGS) $(INC) $(LIB) $(LDFLAGS) -o $@

queue-test: queue-test.c
	$(CC) $< $(CFLAGS) $(INC) $(LIB) $(LDFLAGS) -o $@

stack-test: stack-test.c
	$(CC) $< $(CFLAGS) $(INC) $(LIB) $(LDFLAGS) -o $@

vector-test: vector-test.c
	$(CC) $< $(CFLAGS) $(INC) $(LIB) $(LDFLAGS) -o $@

clean:
	rm circular_linked_list-test linked_list-test queue-test stack-test vector-test

run:
	./circular_linked_list-test
	./linked_list-test
	./queue-test
	./stack-test
	./vector-test
