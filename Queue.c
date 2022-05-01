/*
 * Queue.c
 *
 * FIFO queue structure using an array of
 * Car-type elements stored in it. 
 *
 * This file is based on Queue.h 
 * which contains Queue struct.
 *
 * Author Ahmed Patwa
 * Version 1.00 2022/04/18
 *
 */

#include <pthread.h>		// Provides thread-safe mutex lock
#include <stdbool.h>        	// Provides boolean data type
#include <stdlib.h>
#include <assert.h>
#include "Car.h"		// Provides the required Car type structure

/* =============================================================================
 * FIFO Queue struct holds the queue array and its standard field variables.
 * To implement this queue write the standard queue operations with signatures
 * as listed below. [Qinit(), Qfree(), Qenqueue(), Qserve(), Qpeek(), Qsize(),
 * Qcapacity(), Qclear(), QisEmpty(), and QisFull()].
 *
 * Also use the extra field "list" to write function [Qiterator] that returns
 * a list used to traverse all the elements of the queue starting at the head
 * and ending at the tail without changing the state of the queue.
 * =============================================================================
 */
typedef struct Queue_t {
    Car **data;       		// Array to hold car queue
	Car **list;				// Array to hold car list
    int capacity;      		// The array (queue) capacity
    int count;              // Number of cars currently in the queue
    int tail;             	// The queue tail position
    int head;            	// The queue head position
} Queue;

Queue Q;			// Global Queue variable

bool QisFull();
bool QisEmpty();

/* =============================================================================
 * Initialize the feilds of a Queue structure instance.
 * =============================================================================
 */
void Qinit(int n){
	Q.capacity = n;		// Initialize Capacity
	Q.count = 0;		// Initialize count, head, and tail = 0
	Q.head = 0;
	Q.tail = 0;
	Q.data = malloc(sizeof(Car) * n);	// Allocate memory to data(Size of n cars)
}

/* =============================================================================
 * Free the Queue data and list arrays.
 * =============================================================================
 */
void Qfree(){
	free(Q.list);
	free(Q.data);
}

/* =============================================================================
 * Clear the Queue.
 * =============================================================================
 */
void Qclear(){
	// Return array pointers to their initialization values.
	Q.count = 0;
	Q.head = 0;
	Q.tail = 0;
}

/* =============================================================================
 * A FIFO Queue enqueue function.
 * Check precondition Qisfull() = false.
 * =============================================================================
 */
void Qenqueue(Car *car){
	if(!QisFull()){	
		Q.data[Q.tail] = car;
		Q.count += 1;
		Q.tail  = (Q.tail + 1) % Q.capacity;
	}
}

/* ===========================================================================
 * A FIFO Queue delete function.
 * Delete and return the car at Queue head.
 * Check precondition QisEmpty = false.
 * ===========================================================================
 */
Car* Qserve(){
	if(QisEmpty())
		return NULL;
	
	int temp = Q.head;
	Q.head = (Q.head + 1) % Q.capacity;	
	Q.count -= 1;
	return Q.data[temp];
}

/* ===========================================================================
 * Return the car at the head of the Queue, without deleting it.
 * ===========================================================================
 */
Car* Qpeek(){
	if(QisEmpty())
		return NULL;

	return Q.data[Q.head];
}

/* ===========================================================================
 * Return a list of the queue contents and its size.
 * ===========================================================================
 */
Car** Qiterator(int *sz){
	if(QisEmpty()) 
		return NULL;

	free(Q.list);				// To prevent memory leak then
	Q.list = malloc(sizeof(Car) * Q.count);	// we must allocate memory again.
	*sz = Q.count;

	// Copy the (**data) contents to (**list). 
	// starting from data[head] to data[tail].
	for(int i = 0; i < Q.count; i++){
		Q.list[i] = Q.data[(Q.head+i)%Q.capacity]; // Using % to wrap-around
	}
	return Q.list;
}

/* ===========================================================================
 * Return the capacity of the FIFO Queue.
 * ===========================================================================
 */
int Qcapacity(){
	return Q.capacity;
}

/* ===========================================================================
 * Return the number of cars in the FIFO Queue.
 * ===========================================================================
 */
int Qsize(){
	return Q.count;
}

/* ===========================================================================
 * Return true if the FIFO Queue is full. Return false otherwise.
 * ===========================================================================
 */
bool QisFull(){
	return (Q.count >= Q.capacity);
}

/* ===========================================================================
 * Return true if the FIFO Queue is empty. Return false otherwise.
 * ===========================================================================
 */
bool QisEmpty(){
	return (Q.count == 0);
}


