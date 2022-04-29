#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include"CarPark.h"



// Define limits that were not defined in CarPark.h
#define PARK_MLIMIT	12			// minimum park size
#define VALET_MLIMIT 	1			// minimim number of valets
#define QUEUE_MLIMIT 	3			// minimum queue size
#define EXP_LIMIT	1.50			// maximum expected number of in-coming cars
#define EXP_MLIMIT	0.01			// minimum expected number of in-coming cars


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
int psize, inval, outval, qsize;		// psize: Park Capacity
						// inval: nubmer of in-valets
						// outval: number of out-valets
						// qsize: capacity of arrival queue
float expnum;					// expnum: expected number of arrivals


pthread_mutex_t plk;
Car **park;


int in_valets();


int main(int argc, char *argv[]){
	// initialization of inputs to default values
	psize = PARK_SIZE;
	inval = IN_VALETS;
	outval = OUT_VALETS;
	qsize = QUEUE_SIZE;
	expnum = EXP_CARS;
	int temp_in;
	
	// Input Handling
	if (argc > 1)
	{
		temp_in = atoi(argv[1]);
		if (temp_in > PARK_LIMIT)
			psize = PARK_LIMIT;
		else if (temp_in < PARK_LIMIT)
			psize = PARK_MLIMIT;
		else
			psize = temp_in;
	}
	if (argc > 2)
	{
		temp_in = atoi(argv[2]);
		if (temp_in > VALET_LIMIT)
			inval = VALET_LIMIT;
		else if (temp_in < VALET_MLIMIT)
			inval = VALET_MLIMIT;
		else
			inval = temp_in;
	}
	if (argc > 3)
	{
		temp_in = atoi(argv[3]);
		if (temp_in > VALET_LIMIT)
			outval = VALET_LIMIT;
		else if (temp_in < VALET_MLIMIT)
			outval = VALET_MLIMIT;
		else
			outval = temp_in;
	}
	if (argc > 4)
	{
		temp_in = atoi(argv[4]);
		if (temp_in > QUEUE_LIMIT)
			outval = QUEUE_LIMIT;
		else if (temp_in < QUEUE_MLIMIT)
			outval = QUEUE_MLIMIT;
		else
			outval = temp_in;
	}
	if (argc > 5)
	{
		temp_in = atof(argv[5]);
		if (temp_in > EXP_LIMIT)
			psize = EXP_LIMIT;
		else if (temp_in < EXP_MLIMIT)
			psize = EXP_MLIMIT;
		else
			psize = temp_in;
	}
	
	

	// initialize the queue
	Qinit(5);
	
	// Initialize GUI
	double n;
	pthread_mutex_init(&plk, NULL);		// used by G2DInit
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
