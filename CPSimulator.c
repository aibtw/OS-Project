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
	for(i=0;i<3;){
		Car *temp = malloc(sizeof(Car));
		CarInit(temp);		
		updateStats(0, ++i, 0, 0, 0, 0, 0, 0);
		printf("Car created, ID = %d\n", (*temp).cid);
		Qenqueue(temp);
	}
	
	// Testing Queue.c
	printf("Peeked Car, ID = %d\n", Qpeek()->cid);
	printf("Is empty?: %d, is full? %d, size: %d, capacity: %d\n",
		QisEmpty(), QisFull(), Qsize(), Qcapacity());	
	
	// Testing iterator() function
	//int *list_size = malloc(sizeof(int));
	//Car **waiting = malloc(sizeof(Car)*(*list_size));
 	//waiting = Qiterator(list_size);
	//printf("Size of list: %d\n", *list_size);
	//printf("Last ID: %d\n", waiting[sizeof(Car)*(*list_size-1)]->cid);
	
	// Testing GUI
	double n;
	pthread_mutex_t plk;
	//pthread_mutex_t plk = PTHREAD_MUTEX_INITIALIZER;
	Car **park = malloc(sizeof(Car)*PARK_SIZE);
 	
	G2DInit(park, 16, 5, 2, plk);
	while(true){
	//	n = newCars(0.5);
		updateStats(0, i, 0, 0, 0, 0, 0, 0);
		show();		
	//	printf("Number of new cars: %f\n",n);
		usleep(10);
	}

	usleep(1000000);
	Qfree();



/*
	Qinit(10);
	Car cars[5];
	int n = 0;
	for(n=0;n<5;){
		CarInit(&cars[n]);
		updateStats(0, ++n, 10, 0, 0, 0, 0, 0);
		printf("Car created, ID = %d\n", cars[n-1].cid);
		Qenqueue(&cars[n-1]);
	}

	for(n=0;n<5;n++){
		Car p,c;
		p = *Qpeek();
		c = *Qserve();
		printf("Car peeked , ID = %d\n", p.cid);
		printf("Car fetched, ID = %d\n", c.cid);
	}
*/

/*
	// Note: Print after update directly solved the issue somehow
	Car c0, c1, c2;
	CarInit(&c0);
	updateStats(0, ++n, 10, 0, 0, 0, 0, 0);
	printf("%d\n", c0.cid);
	CarInit(&c1);
	updateStats(0, ++n, 10, 0, 0, 0, 0, 0);
	printf("%d\n", c1.cid);
	CarInit(&c2);	
	updateStats(0, ++n, 10, 0, 0, 0, 0, 0);
	printf("%d\n", c2.cid);
*/



/*
	CarInit(&c0);
	Car c1, c2, c3, c4;	
	CarInit(&c1);
	CarInit(&c2);
	CarInit(&c3);
	CarInit(&c4);
	
	printf("Car 0 ID: %d\n"
	"Car 1 ID: %d\n"
	"Car 2 ID: %d\n"
	//"Car 3 ID: %d\n"
	//"Car 4 ID: %d\n"
	"Staying time of car 0: %lu\n",
		c0.cid, c1.cid, c2.cid,  difftime(c0.ltm, c1.atm));
*/
/*
	Qinit(5);
	Car **cars;  // pointer to group of pointers to cars
	// cars = address
	// *cars = a pointer to car
	// **cars = a car
	cars = malloc(sizeof(Car)*5);
	Car tem;	
	*(cars+sizeof(Car)) = &tem;
	CarInit(cars[sizeof(Car)]);
	//printf("%lu\n", *cars);
	//CarInit(*cars);
	
	updateStats(0, 0, 1, 1, 1, 1, 1, 1);
	Car t, *temp;
	temp = &t;
	CarInit(temp);
	printf("cars[0] id = %d\n", cars[sizeof(Car)]->cid);
	printf("cars[0] id = %d\n", t.cid);
*/	
/*
	Car c0, c1, c2, c3, c4;
	CarInit(&c0);
	updateStats(0, 1, 1, 1, 1, 1, 1, 1);
	CarInit(&c1);
	updateStats(0, 2, 1, 1, 1, 1, 1, 1);
	CarInit(&c2);	
	updateStats(0, 3, 1, 1, 1, 1, 1, 1);
	CarInit(&c3);	
	updateStats(0, 4, 1, 1, 1, 1, 1, 1);
	
	Qenqueue(&c3);
	Qenqueue(&c4);
	
	Qpeek();
	Car *c5 = Qserve();
	Qpeek();
	Car *c6 = Qserve();
	Qpeek();
	//int x = (*c5).cid;
	//int y = (*c6).cid;
	int x = c0.cid;
	int y = c1.cid;	
	int z = c2.cid;
	printf("%d\n",x);	
	printf("%d\n",y);
	printf("%d\n",z);
	
	

	double n;
	pthread_mutex_t plk = PTHREAD_MUTEX_INITIALIZER;
	G2DInit(cars, PARK_SIZE, IN_VALETS, OUT_VALETS, plk);
	while(true){
		n = newCars(0.5); 	
		show();
		printf("%f\n",n);
		sleep(1);
	}
	usleep(1000000);
	free(cars);
	Qfree();
	*/
}

