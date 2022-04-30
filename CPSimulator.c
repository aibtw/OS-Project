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
int oc, nc, pk, rf, nm, sqw, spt, ut;  		// oc: Number of Occupied slots
						// nc: Total created
						// pk: total parked
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


void input_handler(int argc, char *argv[]);
void initializer();

// ========================================================================================================= //
// Monitor thread: updates stats and displays the GUI.
void *monitor(void *args){
	while(true){
		updateStats(oc, nc, pk, rf, nm, sqw, spt, ut);
		show();
		usleep(100000);
	}
}

// in valets
void *in_valets_t(void *param){
	int id = *(int *)param;	// Cast (void *) into (integer *), then get its value
	printf("[in_valets] Thread created with id: %d\n", id);
}

// out valets
void *out_valets_t(void *param){
	int id = *(int *)param;	// Cast (void *) into (integer *), then get its value
	printf("[out_valets] Thread created with id: %d\n", id);
}


// ========================================================================================================= //

int main(int argc, char *argv[]){
	// Initialize global variables to their default values.
	initializer();
	
	// Handle command line inputs
	input_handler(argc, argv);
	
	// Initialize the queue
	Qinit(5);
	
	// Initialize GUI
	double n;
	pthread_mutex_init(&plk, NULL);		// used by G2DInit
	park = malloc(sizeof(Car)*PARK_SIZE);	// This will serve as park space
	G2DInit(park, PARK_SIZE, IN_VALETS, OUT_VALETS, plk);	// initialize graphics
	// Note, IN_VALETS and OUT_VALETS are the default values defined in CarPark.h
	
	// -------------------------------------------------------------------------------------------------- //
	// Thread pools
	pthread_t inv_tid[inval];
	pthread_t outv_tid[outval];
	int *j;
	for(int i = 0; i<inval; i++){
		j = malloc(sizeof(int));
		*j = i;
		pthread_create(&inv_tid[i], NULL, in_valets_t, j);
	}
	/*for(int i = 0; i<outval; i++){
		j = malloc(sizeof(int));
		*j = i;
		pthread_create(&outv_tid[i], NULL, out_valets, i);
	}
	*/
	// Monitor thread
	pthread_t monitor_tid;
	pthread_create(&monitor_tid, NULL, monitor, NULL);
	
	
	// -------------------------------------------------------------------------------------------------- //
	
	// Create cars and show the graphics
	usleep(5000);
	int nc = 0; // Global cars counter. temporary, Fahad should take care of statistics later
	while(true){
		n = newCars(0.5); // Get Poisson distributed number of cars (maybe 1, maybe 3, no one knows)
		printf("Number of new cars: %f\n",n);
		// Create n cars:
		for(int i = 0; i<n; i++){
			Car *temp = malloc(sizeof(Car));	// Allocate memory to Car pointer
			CarInit(temp);				// Initialize car
			++nc;					// increment number of created cars
			printf("Car created, ID = %d\n", (*temp).cid);
			if(QisFull()){
				printf("Queue is full. Reject the car\n"); // Reject the car
				rf++;				// increament number of rejected cars
			}
			else Qenqueue(temp);			// Enqueue the car
		}
		while(getchar() != '\n');			// wait for ENTER
		//sleep(1);
	}

	usleep(1000000);
	Qfree();
}


// ========================================================================================================= //


void initializer(){
	// initialization of inputs to default values
	psize = PARK_SIZE;
	inval = IN_VALETS;
	outval = OUT_VALETS;
	qsize = QUEUE_SIZE;
	expnum = EXP_CARS;
	oc = 0, nc = 0, pk = 0, rf = 0, nm = 0, sqw = 0, spt = 0, ut = 0;
}


void input_handler(int argc, char *argv[]){
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
}



