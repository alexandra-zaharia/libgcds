CC=gcc
CFLAGS=-g -Wall -Wextra -Wpedantic -Wconversion 

# INC specifies where libgcds header files are located
INC=-I../build/include

# LIB specifies where the static library libgcds.a is located
LIB=-L ../build/lib

# Tell the linker to link with libgcds and libcmocka
LDFLAGS=-lgcds -lcmocka

all: linked_list-test queue-test stack-test vector-test

linked_list-test: linked_list-test.c
	$(CC) $< $(CFLAGS) $(INC) $(LIB) $(LDFLAGS) -o $@

queue-test: queue-test.c
	$(CC) $< $(CFLAGS) $(INC) $(LIB) $(LDFLAGS) -o $@

stack-test: stack-test.c
	$(CC) $< $(CFLAGS) $(INC) $(LIB) $(LDFLAGS) -o $@

vector-test: vector-test.c
	$(CC) $< $(CFLAGS) $(INC) $(LIB) $(LDFLAGS) -o $@

clean:
	rm linked_list-test queue-test stack-test vector-test

run:
	./linked_list-test
	./queue-test
	./stack-test
	./vector-test
