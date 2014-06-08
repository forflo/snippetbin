CF = $(shell pkg-config --cflags --libs libffi)

all: ffitest.c
	gcc -g -o ffitest ffitest.c $(CF)
