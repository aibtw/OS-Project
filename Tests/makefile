CC=gcc
CFLAGS=-c -std=gnu11 -O -g
LIBS= -lSDL_bgi -l SDL2 -pthread -lm
MAIN_FILE=test_queue

all: cp

cp: ../CarPark.o ../Queue.o $(MAIN_FILE).o ../Car.h ../Queue.h ../CarPark.h
	$(CC) ../CarPark.o ../Queue.o $(MAIN_FILE).o -o cp $(LIBS)

Queue.o: Queue.c Queue.h
	$(CC) $(CFLAGS) Queue.c

CPSimulator.o: $(MAIN_FILE).c
	$(CC) $(CFLAGS) $(MAIN_FILE).c

clean:
	rm cp Queue.o $(MAIN_FILE).o

