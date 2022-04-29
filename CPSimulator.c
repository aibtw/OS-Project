#include<stdio.h>
#include<stdlib.h>
#include<time.h>
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
	
	usleep(5000);
	int j = 1;
	while(true){
		n = newCars(0.5);
		printf("Number of new cars: %f\n",n);
		for(int i = 0; i<n; i++){
			Car *temp = malloc(sizeof(Car));
			CarInit(temp);		
			updateStats(0, j++, 0, 0, 0, 0, 0, 0);
			printf("Car created, ID = %d\n", (*temp).cid);
			if(QisFull()){
				printf("Queue is full. Reject the car\n");
			}
			else Qenqueue(temp);
		}
		show();
		while(getchar() != '\n');
		//sleep(1);
	}

	usleep(1000000);
	Qfree();
}
