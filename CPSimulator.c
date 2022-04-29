#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include"CarPark.h"

pthread_mutex_t plk;
Car **park;

// Statistical variables
int oc, nc, pk, rf, nm, sqw, spt, ut;  		// oc: Total Occupied,
						// nc: Total created,
						// pk: total parked, 
						// rf: total refused
						// nm: Currently Aquired by in-valets
						// sqw: sum of car waiting times in arrival queue
						// spt: sum of car parking times
						// ut: current park utilization

// input variables
int psize, inval, outval, qsize, expnum;	// psize: Park Capacity
						// inval: nubmer of in-valets
						// outval: number of out-valets
						// qsize: capacity of arrival queue
						// expnum: expected number of arrivals


int in_valets();

int main(int argc, char *argv[]){
	pthread_mutex_init(&plk, NULL);		// used by G2DInit

	// initialize the queue
	Qinit(5);
	
	// Initialize GUI
	double n;
	park = malloc(sizeof(Car)*PARK_SIZE);	// This will serve as park space
	G2DInit(park, PARK_SIZE, IN_VALETS, OUT_VALETS, plk);	// initialize graphics
	// Note, IN_VALETS and OUT_VALETS are the default values defined in CarPark.h
	
	
	
	// Create cars and show the graphics
	usleep(5000);
	int j = 1; // Global cars counter. temporary, Fahad should take care of statistics later
	while(true){
		n = newCars(0.5); // Get Poisson distributed number of cars (maybe 1, maybe 3, no one knows)
		printf("Number of new cars: %f\n",n);
		// Create n cars:
		for(int i = 0; i<n; i++){
			Car *temp = malloc(sizeof(Car));	// Allocate memory to Car pointer
			CarInit(temp);				// Initialize car
			updateStats(0, j++, 0, 0, 0, 0, 0, 0);	// temporary. Take care of all other stats later
			printf("Car created, ID = %d\n", (*temp).cid);
			if(QisFull()){
				printf("Queue is full. Reject the car\n"); // Reject the car
			}
			else Qenqueue(temp);			// Enqueue the car
		}
		show();						// Show the graphics
		while(getchar() != '\n');			// wait for ENTER
		//sleep(1);
	}

	usleep(1000000);
	Qfree();
}
