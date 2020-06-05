CC = gcc
FLAGS = -Wall -g

# $@ - the file on the left side of the :
# $< - the first name in the dependencies list
# $^ - the right side of :

all: IPC run

run: IPC
	./IPC

IPC: main.o
	$(CC) $(FLAGS) -o $@ $^

main.o: main.c
	$(CC) $(FLAGS) -c $<

.PHONY: clean all run

clean:
	rm -f *.o *.out IPC
