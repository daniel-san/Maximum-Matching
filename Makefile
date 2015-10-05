CC = gcc
CFLAGS = -Wall

default: all

all:
	cd C; ${CC} ${CFLAGS} -c *.c
	cd C/test; ${CC} ${CFLAGS} adt.c -o adt \
				../adt.o
	cd C/test; ${CC} ${CFLAGS} graph.c -o graph \
				../adt.o \
				../graph.o
	cd C/test; ${CC} ${CFLAGS} search.c -o search \
				../adt.o \
				../graph.o
	cd C/test; ${CC} ${CFLAGS} graph_generator.c -o graph_generator \
				../graph.o \
				../adt.o \
				../graph_generator.o
	cd C/test; ${CC} ${CF:AGS} mv.c -o mv \
				../adt.o \
				../mv_graph.o \
				../mv.o
clean:
	cd C; rm -rf *.o
	cd C/test; rm -rf graph graph_generator search mv adt
