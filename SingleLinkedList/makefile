CC=gcc

CFLAGS=-c -Wall

all: testing
	./testing
	make clean

testing: main.o sll.o
	$(CC) main.o sll.o -o testing

main.o: main.c
	$(CC) $(CFLAGS) main.c

list.o: sll.c
	$(CC) $(CFLAGS) sll.c

clean:
	rm -rf *.o testing

