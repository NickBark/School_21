CC=gcc
CFLAGS=-Wall -Werror -Wextra
EXECUTABLE=../build/Quest_1

all: state_sort 

state_sort: state_sort.o 
	$(CC) $(CFLAGS) state_sort.o -o $(EXECUTABLE)

state_sort.o: 
	$(CC) -c $(CFLAGS) state_sort.c -o state_sort.o
clean:
	rm -f *.o
	rm -f ../build/*

rebuild: clean all
