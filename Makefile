CC = gcc
CFLAGS = -Wall

default: all

all:
	cd C; ${CC} ${CFLAGS} -c *.c
	cd C/test; ${CC} ${CFLAGS} graph.c -o graph \
				../adt.o \
				../graph.o
	cd C/test; ${CC} ${CFLAGS} search.c -o search \
				../adt.o \
				../graph.o
clean:
	cd C; rm -rf *.o
	cd C/test; rm -rf graph search
