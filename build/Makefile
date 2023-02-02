CC=gcc
CFLAG= -Wall
CFLAGS= -Wall -c

ALL : prog

prog: main.o functions.o
	$(CC) $(CFLAG) $^ -o $@

main.o: ../src/main.c ../include/structures.h
	$(CC) $(CFLAGS) $<

functions.o: ../src/files/functions.c ../include/functions.h ../include/structures.h
	$(CC) $(CFLAGS) $<

.PHONY : clean
clean :
	rm prog.exe *.o