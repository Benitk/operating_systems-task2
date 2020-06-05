CC = gcc
FLAGS = -pthread

# $@ - the file on the left side of the :
# $< - the first name in the dependencies list
# $^ - the right side of :

all: 2_3_1 2_2_1 2_1_1 2_1_2 2_2_2 2_3_2

2_3_2: 2_3_2.o
	$(CC) $(FLAGS) -o $@ $^

2_3_2.o: 2_3_2.c
	$(CC)  -c $<

2_2_2: 2_2_2.o
	$(CC) $(FLAGS) -o $@ $^

2_2_2.o: 2_2_2.c
	$(CC)  -c $<

2_1_2: 2_1_2.o
	$(CC) $(FLAGS) -o $@ $^

2_1_2.o: 2_1_2.c
	$(CC)  -c $<

2_3_1: 2_3_1.o
	$(CC) $(FLAGS) -o $@ $^

2_3_1.o: 2_3_1.c
	$(CC) -c $<


2_2_1: 2_2_1.o
	$(CC) $(FLAGS) -o $@ $^

2_2_1.o: 2_2_1.c
	$(CC) -c $<

2_1_1: 2_1_1.o
	$(CC) $(FLAGS) -o $@ $^

2_1_1.o: 2_1_1.c
	$(CC)  -c $<

.PHONY: clean all

clean:
	rm -f *.o *.out 2_3_1 2_2_1 2_1_1 2_1_2 2_2_2 2_3_2
