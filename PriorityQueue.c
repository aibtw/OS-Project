/*
 * PriorityQueue
 *
 * Author Ahmed Patwa
 * Version 1.00 2022/04/30
 *
 */

#include <pthread.h>		// Provides thread-safe mutex lock
#include <stdbool.h>        	// Provides boolean data type
#include <stdlib.h>
#include "Car.h"		// Provides the required Car type structure

/* =============================================================================
	.......
 * =============================================================================
 */
typedef struct PQueue_t {
    Car **data;       		// Array to hold car queue
    int capacity;      		// The array (queue) capacity
    int count;              	// Number of cars currently in the queue
} PQueue;

PQueue PQ;			// Global Queue variable

bool PQisFull();
bool PQisEmpty();

/* =============================================================================
 * Initialize the feilds of a Queue structure instance.
 * =============================================================================
 */
void PQinit(int n){
	PQ.capacity = n;	// Initialize Capacity
	PQ.count = 0;		// Initialize count, head, and tail = 0
	PQ.data = malloc(sizeof(Car) * n);	// Allocate memory to data(Size of n cars)
}

/* =============================================================================
 * Free the Queue data and list arrays.
 * =============================================================================
 */
void PQfree(){
	free(PQ.data);
}

/* =============================================================================
 * Clear the Queue.
 * =============================================================================
 */
void Qclear(){
	// Return array pointers to their initialization values.
	PQ.count = 0;
}

/* =============================================================================
 * Sifting up.
 * =============================================================================
 */
void siftUp(int i)
{
	int parent = (i-1)/2;
	double parent_p = PQ[parent]->ltm + PQ[parent]->ptm;
	double i_p = PQ[i]->ltm + PQ[i]->ptm;
	
	if(i > 0 && parent_p < i_p) {
		// Swap parent and current node
		swap(parent_p, i_p);
		// Update i to parent of i
		i = parent;
		siftUp(i);
	}
}

/* =============================================================================
 * Sifting down.
 * =============================================================================
 */
void siftDown(int i)
{
	// Parent (current node)
	int maxIndex = i;

	// Left Child
	int l = 2 * i + 1;
	// Right Child
	int r = 2 * i + 2;
	
	// priorities
	i_p  = PQ[i]->ltm + PQ[i]->ptm  // current node priority
	l_p  = PQ[l]->ltm + PQ[l]->ptm  // left node priority
	r_p  = PQ[r]->ltm + PQ[r]->ptm  // right node priority
	
	if (l <= count && l_p > i_p) {
		maxIndex = l;
	}
	
	if (r <= size && r_p > i_p) {
		maxIndex = r;
	}

	// If i not same as maxIndex
	if (i != maxIndex) {
		swap(PQ[i], PQ[maxIndex]);
		shiftDown(maxIndex);
	}
}


/* =============================================================================
 * Park a car in the priority queue
 * =============================================================================
 */
void PQenqueue(Car *car){
	if(!PQisFull()){	
		PQ.data[count] = car;
		PQ.count += 1;
		siftUp(count);
	}
}

/* ===========================================================================
 * Unpark a car from the priority queue
 * ===========================================================================
 */
Car* PQserve(){
	if(PQisEmpty())
		return NULL;
	
	Car *temp = PQ[0];
	// Replace the value at the root
	// with the last leaf
	PQ[0] = PQ[count];
	count --;

	// Shift down the replaced element
	// to maintain the heap property
	siftDown(0);
	return temp;
}

/* ===========================================================================
 * Return the car at the root of the Queue, without deleting it.
 * ===========================================================================
 */
Car* PQpeek(){
	if(PQisEmpty())
		return NULL;

	return PQ.data[0];
}


/* ===========================================================================
 * Return the capacity of the Queue.
 * ===========================================================================
 */
int PQcapacity(){
	return PQ.capacity;
}

/* ===========================================================================
 * Return the number of cars in the Queue.
 * ===========================================================================
 */
int PQsize(){
	return PQ.count;
}

/* ===========================================================================
 * Return true if the Queue is full. Return false otherwise.
 * ===========================================================================
 */
bool PQisFull(){
	return (PQ.count >= PQ.capacity);
}

/* ===========================================================================
 * Return true if the Queue is empty. Return false otherwise.
 * ===========================================================================
 */
bool PQisEmpty(){
	return (PQ.count == 0);
}


