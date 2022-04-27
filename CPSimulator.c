#include<stdio.h>
#include<time.h>
//#include"Queue.h"
#include<unistd.h>
#include"CarPark.h"
// No need for car.h, it is included in queue.h


int main(int argc, char argv[]){
	// initialize the queue
	
	Qinit(5);
	int i = 0;
	
	
	// Create i cars
	for(i=0;i<5;){
		Car *temp = malloc(sizeof(Car));
		CarInit(temp);		
		updateStats(0, ++i, 0, 0, 0, 0, 0, 0);
		printf("Car created, ID = %d\n", (*temp).cid);
		Qenqueue(temp);
	}
	
	// Testing Queue.c
	printf("Peeked Car, ID = %d\n", Qpeek()->cid);
	printf("Peeked Car, image = %s\n", Qpeek()->pn);
	printf("Is empty?: %d, is full? %d, size: %d, capacity: %d\n",
		QisEmpty(), QisFull(), Qsize(), Qcapacity());	
	
	// Testing iterator() function
	int *list_size = malloc(sizeof(int));
	Car **waiting = malloc(sizeof(Car)*(*list_size));
 	waiting = Qiterator(list_size);
	printf("Size of list: %d\n", *list_size);
	printf("Last ID: %d\n", waiting[sizeof(Car)*(*list_size-1)]->cid);
	
	// Testing GUI
	double n;
	pthread_mutex_t plk;
	//pthread_mutex_t plk = PTHREAD_MUTEX_INITIALIZER;
	Car **park = malloc(sizeof(Car)*PARK_SIZE);
 	
	G2DInit(park, 16, 5, 2, plk);
	while(true){
	//	n = newCars(0.5);
		show();
	//	printf("Number of new cars: %f\n",n);
		usleep(10);
	}

	usleep(1000000);
	Qfree();
}

