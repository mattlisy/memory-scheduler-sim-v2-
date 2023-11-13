#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "process.h"

// type definition for the priority Queue data structure
typedef struct {
    Process_node* head;
    Process_node* tail;
    int size;
} priority_Queue;

// returns the size of the priority Queue

int sizeof_PQueue(const priority_Queue pQ);

// creates a priority Queue data structure
priority_Queue create_PQueue();

// removes node at front and returns the value 
Process PQ_dequeue(priority_Queue* pQ);

// returns the value at front of priority Queue
Process PQ_peek(const priority_Queue* pQ);

// adds a new node with data from process to the priority Queue
void PQ_enqueue(priority_Queue* pQ, const Process process);

// prints the priority Queue to terminal
void print_PQueue(const priority_Queue pQ);

// free all nodes from the priority Queue
void destroy_PQueue(priority_Queue* pQ);

//increment wait time for report
void incr_wait_time_PQueue(priority_Queue* pQ);
#endif

