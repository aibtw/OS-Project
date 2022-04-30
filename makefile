CC=gcc
CFLAGS=-c -std=gnu11 -O -g
LIBS= -lSDL_bgi -l SDL2 -pthread -lm

all: cp

cp: CarPark.o Queue.o CPSimulator.o Car.h Queue.h CarPark.h
	$(CC) CarPark.o Queue.o PriorityQueue.o CPSimulator.o -o cp $(LIBS)

Queue.o: Queue.c Queue.h
	$(CC) $(CFLAGS) Queue.c

PriorityQueue.o: PriorityQueue.c PriorityQueue.h
	$(CC) $(CFLAGS) PriorityQueue.c
	
CPSimulator.o: CPSimulator.c
	$(CC) $(CFLAGS) CPSimulator.c

clean:
	rm cp Queue.o PriorityQueue.o CPSimulator.o

