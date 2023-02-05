CC=gcc
CFLAGS= -Wall -c

ALL : prog

prog: main.o Functions.o Liste.o Malloc.o Set.o
	$(CC) -Wall $^ -o $@

main.o: ../src/main.c ../include/includes.h ../include/Functions.h ../include/Struct.h ../include/Liste.h ../include/Malloc.h ../include/Set.h
	$(CC) $(CFLAGS) $<
Functions.o: ../src/files/Functions.c ../include/Functions.h ../include/Struct.h
	$(CC) $(CFLAGS) $<
Liste.o: ../src/files/Liste.c ../include/Liste.h ../include/Struct.h
	$(CC) $(CFLAGS) $<
Malloc.o: ../src/files/Malloc.c ../include/Malloc.h ../include/Struct.h
	$(CC) $(CFLAGS) $<
Set.o: ../src/files/Set.c ../include/Set.h ../include/Struct.h
	$(CC) $(CFLAGS) $<

.PHONY : clean
clean :
	rm prog.exe *.o