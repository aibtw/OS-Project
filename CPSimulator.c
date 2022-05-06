#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>
#include<semaphore.h>

#include"CarPark.h"
#include"PriorityQueue.h"


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
pthread_mutex_t Qlock;
pthread_mutex_t PQlock;

sem_t PQempty; 					// Counting semaphore to wait till PQ isn't full
sem_t PQfull;

void initializer();
void input_handler(int argc, char *argv[]);
int getRandom(int lower, int upper);

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
	int id = *(int *)param;		// Cast (void *) into (integer *), then get its value
	printf("[in_valets] Thread created with id: %d\n", id);
	setViState(id, READY);		// in Valet Ready!
	
	while(true){
		setViState(id, READY);			// if yes, change valet state to fetch
		usleep(1000); // NOTE: BUSY WAITING !!
		
		pthread_mutex_lock(&Qlock);		// Lock valets' access to Queue
		if(!QisEmpty()){			// Check if there are available cars
			setViState(id, FETCH);		// if yes, change valet state to fetch
			usleep(getRandom(0,200000)); 	// pause in the critical section
			Car *c = Qserve();		// Fetch a car from Queue
			setViCar(id, c);		// Assign this valet to the served car
			sqw += time(NULL) - c->atm;	// Update stats
			nm++;
			c->vid = id;			// Assign vid to the car
			pthread_mutex_unlock(&Qlock);	// Unlock valets' access to Queue

			setViState(id, WAIT);		// Wait access to park
			sem_wait(&PQempty);		// 
			pthread_mutex_lock(&PQlock);	// Lock access to PQ
			setViState(id, MOVE);		// State: Parking the car
			usleep(getRandom(0, 1000000)); 	// pause before parking
			c->ptm = time(NULL);		// Set parking time
			PQenqueue(c);			// Park the car
			oc++;
			pk++;
			sem_post(&PQfull);		// Increment occupied spaces sem
			pthread_mutex_unlock(&PQlock);
		
		} else pthread_mutex_unlock(&Qlock);	// Q is empty, so unlock valets' access to Queue
	}
}

// out valets
void *out_valets_t(void *param){
	int id = *(int *)param;	// Cast (void *) into (integer *), then get its value
	printf("[out_valets] Thread created with id: %d\n", id);
	setVoState(id, READY);				// out Valet Ready!
	
	while(true){
		setVoState(id, READY);			// out Valet Ready!
		usleep(1000000);// NOTE: BUSY WAITING !!
		sem_wait(&PQfull);
		pthread_mutex_lock(&PQlock);
		Car *c = PQpeek();
		printf("Car at head ID: %d, ltm: %lu, parktime: %lu\n", c->cid, c->ltm, c->ptm);
		if (c->ptm + c->ltm < time(NULL)){
			//critical section
			printf("Removing...\n");
			usleep(getRandom(0, 200000)); //pause inside critical section
			PQserve();
			sem_post(&PQempty);
			oc--;
			spt = spt + time(NULL) - c->ptm;
			pthread_mutex_unlock(&PQlock);
			usleep(getRandom(0, 1000000)); //pause after unparking a car
		}
		else {
			pthread_mutex_unlock(&PQlock); 
			sem_post(&PQfull);
		}
		
	}
}

// Interrupt handler
void int_handler(){
	printf("\nReceiveed Inturrept! Exiting ... \n");
	finish();
	Qfree();
	PQfree();
	exit(0);
}

int getRandom(int lower, int upper) {
	int num = (rand()%(upper-lower +1 )) + lower;
	return num;
	
}


// ========================================================================================================= //
  
int main(int argc, char *argv[]){
	// Initialize global variables to their default values.
	initializer();
	
	// Handle command line inputs
	input_handler(argc, argv);
	
	// Initialize the queue
	Qinit(qsize);
	
	// Initialize the park
	PQinit(psize);
	
	printf("[main] Initialized!\n");
	printf("[main] psize: %d, inval: %d, outval: %d, qsize: %d, expnum: %f\n", psize, inval, outval, qsize, expnum);
	
	
	// Initialize GUI
	double n;
	pthread_mutex_init(&plk, NULL);			// used by G2DInit
	G2DInit(PQ.data, psize, inval, outval, plk);	// initialize graphics
	
	// Signaling
	signal(SIGINT, int_handler);
	
	// -------------------------------------------------------------------------------------------------- //
	// Thread pools
	pthread_t inv_tid[inval];
	pthread_t outv_tid[outval];
	int *j;
	for(int i = 0; i<inval; i++){
		j = malloc(sizeof(int));		// j will provide unique id to each valet
		*j = i;
		pthread_create(&inv_tid[i], NULL, in_valets_t, j);
	}
	for(int i = 0; i<outval; i++){
		j = malloc(sizeof(int));
		*j = i;
		pthread_create(&outv_tid[i], NULL, out_valets_t, j);
	}
	
	
	usleep(100000);
	free(j);
	
	// Monitor thread
	pthread_t monitor_tid;
	pthread_create(&monitor_tid, NULL, monitor, NULL);
	
	
	// -------------------------------------------------------------------------------------------------- //
	
	// Create cars and show the graphics
	usleep(5000);
	Car *c;
	while(true){
		n = newCars(0.5); // Get Poisson distributed number of cars (maybe 1, maybe 3, no one knows)
		// Create n cars:
		for(int i = 0; i<n; i++){
			c = malloc(sizeof(Car));		// Allocate memory to Car pointer
			CarInit(c);				// Initialize car
			++nc;					// increment number of created cars
			printf("Car created, ID = %d\n", (*c).cid);
			pthread_mutex_lock(&Qlock);
			if(QisFull()){
				printf("Queue is full. Reject the car\n"); // Reject the car
				rf++;				// increament number of rejected cars
				free(c);
				c = NULL;
			}
			else Qenqueue(c);			// Enqueue the car
			pthread_mutex_unlock(&Qlock);
			// NOTE: I think we shouldn't update stats here, but it is necessary (otherwise
			// duplicate id will be given). So, i guess we must have a lock at ++rf so that 
			// it only increments if updateStates is done. 
			//updateStats(oc, nc, pk, rf, nm, sqw, spt, ut);
		}
		
		//while(getchar() != '\n');			// wait for ENTER
		sleep(1);
		//usleep(250000);
	}
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
	srand(time(0));
	
	if (pthread_mutex_init(&Qlock, NULL) != 0) {
		printf("\n mutex init has failed\n");
		exit(0);
	}
	if (pthread_mutex_init(&PQlock, NULL) != 0) {
		printf("\n mutex init has failed\n");
		exit(0);
	}

	sem_init(&PQempty, 0, psize);
	sem_init(&PQfull, 0, 0);
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



