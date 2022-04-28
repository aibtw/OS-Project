#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//#include"Queue.h"
#include<unistd.h>
#include<string.h>
#include"CarPark.h"

pthread_mutex_t plk;
Car **park;

int main(int argc, char argv[]){
	pthread_mutex_init(&plk, NULL);

	// initialize the queue
	Qinit(5);

	// Initialize GUI
	double n;
	park = malloc(sizeof(Car)*PARK_SIZE);
	G2DInit(park, PARK_SIZE, 5, 2, plk);

	// Create i cars
	int c = 5;
	for(int i=0;i<c;){
		Car *temp = malloc(sizeof(Car));
		CarInit(temp);		
		updateStats(0, ++i, 0, 0, 0, 0, 0, 0);
		printf("Car created, ID = %d\n", (*temp).cid);
		Qenqueue(temp);
	}
	Car *toPark = Qserve();
	park[0] = toPark;	
	
	// Testing Queue.c
	printf("Peeked Car, ID = %d\n", Qpeek()->cid);
	printf("Peeked Car, image = %s\n", Qpeek()->pn);
	printf("Is empty?: %d, is full? %d, size: %d, capacity: %d\n",
		QisEmpty(), QisFull(), Qsize(), Qcapacity());	
	
	// Testing iterator() function
	int *list_size = malloc(sizeof(int));
	Car **waiting = malloc(sizeof(Car)*c);
 	waiting = Qiterator(list_size);
	printf("Size of list: %d\n", *list_size);
	printf("First  ID: %d\n", waiting[0]->cid);
	printf("Second ID: %d\n", waiting[1]->cid);
	printf("Third  ID: %d\n", waiting[2]->cid);
	printf("Forth  ID: %d\n", waiting[3]->cid);
	//printf("Fifth  ID: %d\n", waiting[sizeof(Car)*4]->cid);
	usleep(5000);
	while(true){
		n = newCars(0.5);
		show();
		printf("Number of new cars: %f\n",n);
		sleep(1);
	}

	usleep(1000000);
	Qfree();
}
