/*
 * PriorityQueue.c
 *
 * Priority Queue Structure using an array of
 * Car-type elements stored in it.
 *
 * The priority of this queue is based on the waiting time of 
 * each car which is defined as (parking time + stay time).
 *
 * Author Ahmed Patwa
 * Version 1.00 2022/04/30
 *
 */

#include <pthread.h>		// Provides thread-safe mutex lock
#include <stdbool.h>        	// Provides boolean data type
#include <stdlib.h>
#include <stdio.h>
#include "Car.h"

/* =============================================================================
 * PQueue Structure has a data array, and a field for maximum capacity
 * and a counter for number of elements in the queue.
 * =============================================================================
 */
typedef struct PQueue_t {
    Car **data;       		// Array to hold car queue
    int capacity;      		// The array (queue) capacity
    int count;              	// Number of cars currently in the queue
} PQueue;

PQueue PQ;

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
void PQclear(){
	// Return array pointers to their initialization values.
	PQ.count = 0;
}

/* =============================================================================
 * swap two values in PQ.data.
 * =============================================================================
 */
void swap(int i, int j) {
	Car *temp = PQ.data[i];
	PQ.data[i] = PQ.data[j];
	PQ.data[j] = temp;
}


/* =============================================================================
 * Sifting up.
 * =============================================================================
 */
void siftUp(int i)
{
	if(i > 0){
		int parent = (int) ((i-1)/2);
		double parent_p = PQ.data[parent]->ltm + PQ.data[parent]->ptm;
		double i_p = PQ.data[i]->ltm + PQ.data[i]->ptm;
		
		if(parent_p > i_p) {
			// Swap parent and current node
			swap(parent, i);
			// Update i to parent of i
			i = parent;
			siftUp(i);
		}
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
	int maxIndex1 = i;
	int maxIndex2 = i;
	// Left Child
	int l = 2 * i + 1;
	// Right Child
	int r = 2 * i + 2;
	
	// priorities
	long i_p  = PQ.data[i]->ltm + PQ.data[i]->ptm;  // current node priority
	
	
	long long l_p = 9223372036854775807;
	long long r_p = 9223372036854775807;
	if (l < PQ.count) {
		l_p  = PQ.data[l]->ltm + PQ.data[l]->ptm;  // left node priority
		if (l_p < i_p)
			maxIndex1 = l;
	}
	
	if (r < PQ.count) {
		r_p  = PQ.data[r]->ltm + PQ.data[r]->ptm;  // right node priority
		if (r_p < i_p)
			maxIndex2 = r;
		
	}
	
	if (r_p < l_p){
		maxIndex = maxIndex2;
	}else{
		maxIndex = maxIndex1;
	}
	// If i not same as maxIndex
	if (i != maxIndex) {
		swap(i, maxIndex);
		siftDown(maxIndex);
	}
}


/* =============================================================================
 * Park a car in the priority queue
 * =============================================================================
 */
void PQenqueue(Car *car){
	
	if(!PQisFull()){
		PQ.data[PQ.count] = car;
		siftUp(PQ.count);
		PQ.count += 1;
	}
}

/* ===========================================================================
 * Unpark a car from the priority queue
 * ===========================================================================
 */
Car* PQserve(){
	if(PQisEmpty())
		return NULL;
	
	Car *temp = PQ.data[0];
	// Replace the value at the root
	// with the last leaf
	PQ.count --;
	PQ.data[0] = PQ.data[PQ.count];
	PQ.data[PQ.count] = NULL;
	// Sift down the replaced element
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


