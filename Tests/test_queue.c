#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//#include"Queue.h"
#include<unistd.h>
#include<string.h>
#include"../CarPark.h"


int main(int argc, char argv[]){


	// initialize the queue
	Qinit(5);
	printf("Is empty?: %d, is full? %d, size: %d, capacity: %d\n",
		QisEmpty(), QisFull(), Qsize(), Qcapacity());	
	// Create i cars
	int c = 5;
	for(int i=0;i<c;){
		Car *temp = malloc(sizeof(Car));
		CarInit(temp);		
		updateStats(0, ++i, 0, 0, 0, 0, 0, 0);
		printf("Car created, ID = %d\n", (*temp).cid);
		Qenqueue(temp);
	}
	printf("Is empty?: %d, is full? %d, size: %d, capacity: %d\n",
		QisEmpty(), QisFull(), Qsize(), Qcapacity());	
	printf("Serving first car: ");
	Car *toPark = Qserve();
	printf("... Done! it has the ID = %d\n", toPark->cid);
	
	// Testing Queue.c
	printf("Peeked Car, ID = %d\n", Qpeek()->cid);
	printf("Is empty?: %d, is full? %d, size: %d, capacity: %d\n",
		QisEmpty(), QisFull(), Qsize(), Qcapacity());	
	
	// Testing iterator() function
	int *list_size = malloc(sizeof(int));
	Car **waiting = malloc(sizeof(Car)*c);
 	waiting = Qiterator(list_size);
 	printf("Size of list: %d\n", *list_size);
 	for (int i = 0; i < *list_size; i++){	
		printf("car number {%d} has ID: %d\n", i, waiting[i]->cid);
	}

	Qfree();
}
