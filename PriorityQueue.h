/*
 * PriorityQueue.h
 *
 * Header file for a priority queue structure using an array of
 * Car-type elements stored in it.
 *
 * The priority of this queue is based on the waiting time of 
 * each car which is defined as (parking time + stay time).
 * 
 * Author Ahmed Patwa
 * Version 1.00 2022/04/30
 *
 */
 

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

/* =============================================================================
 * Initialize the feilds of a Queue structure instance.
 * =============================================================================
 */
void PQinit(int n);

/* =============================================================================
 * Free the Queue data and list arrays.
 * =============================================================================
 */
void PQfree();

/* =============================================================================
 * Clear the Queue.
 * =============================================================================
 */
void Qclear();

/* =============================================================================
 * Sifting up.
 * =============================================================================
 */
void siftUp(int i);

/* =============================================================================
 * Sifting down.
 * =============================================================================
 */
void siftDown(int i);

/* =============================================================================
 * Park a car in the priority queue
 * =============================================================================
 */
void PQenqueue(Car *car);
/* ===========================================================================
 * Unpark a car from the priority queue 
 * ===========================================================================
 */
Car* PQserve();

/* ===========================================================================
 * Return the car at the root of the Queue, without deleting it.
 * ===========================================================================
 */
Car* PQpeek();


/* ===========================================================================
 * Return the capacity of the Queue.
 * ===========================================================================
 */
int PQcapacity();

/* ===========================================================================
 * Return the number of cars in the Queue.
 * ===========================================================================
 */
int PQsize();

/* ===========================================================================
 * Return true if the Queue is full. Return false otherwise.
 * ===========================================================================
 */
bool PQisFull();

/* ===========================================================================
 * Return true if the Queue is empty. Return false otherwise.
 * ===========================================================================
 */
bool PQisEmpty();


