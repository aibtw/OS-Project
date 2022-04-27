/*
 * Car.c
 * Implements Car.h functions
 *
 * Author Ahmed Patwa
 * Version 1.00 2022/04/17
 *
 */
#include<time.h>
#include<stdio.h>

int cid;

typedef struct Car_t {
	int cid;				// The car's unique ID
	int vid;				// The in-valet's ID
	int sno;				// The parking slot number
	time_t atm;				// The time of arrival (creation)
	time_t ptm;				// The time of parking (start time)
	time_t ltm;				// The expected time to leave (end time)
	char pn[20];			// The car's image file name
	char pnf[20];			// The car's flipped-image file name
} Car;

/* =============================================================================
 * CarInit:
 * Initialize the newly created car passed in the parameter. Before using a new
 * car it must be initialized by a call to this function which is implemented
 * in the CarPark.o file.
 * Note: This function does not create a car object.
 * =============================================================================
 * Initialize the newly created car by setting the following fields:
 *  - cid is set to a unique car ID.
 *  - sno is set to 0.
 *  - atm is set to the current time -- time of creation.
 *  - ltm is set to a random time limited to 180 seconds -- time to stay parked.
 *  - pn  is set to the file name of a random car image limited to 13.
 *  - pnf is set to the file name of the horizontaly flipped same image as pn.
 * =============================================================================
 */
void CarInit(Car *car){
	/*time_t atm, ltm;
	atm = time(NULL);	// Creation time
	ltm = atm + 5;		// Expected leaving time 

	// [NOTE] cid should be protected !
	(*car).cid = cid++;
	(*car).atm = atm;
	(*car).ltm = ltm;
	*/
	// set pn and pnf
	// --------------
}

