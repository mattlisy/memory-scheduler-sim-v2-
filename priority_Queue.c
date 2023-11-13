#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "priority_Queue.h"

// returns the size of the priority Queue
int sizeof_PQueue(const priority_Queue pQ) {
	return pQ.size;
}

// creates a priority Queue data structure
priority_Queue create_PQueue() {
   	priority_Queue new;
    	new.head = new.tail = NULL;
    	new.size = 0;
    	return new;
}

// returns the value at front of priority Queue
Process PQ_peek(const priority_Queue* pQ) {
	assert(pQ->size != 0);
	return pQ->head->process;
}
	
// removes node at front and returns the value 
Process PQ_dequeue(priority_Queue* pQ) {
    	assert(pQ != NULL);
    	assert(pQ->size != 0);
    	Process rValue = pQ->head->process;
    	Process_node* old = pQ->head;
    	if (pQ->size == 1) {
       		pQ->head = NULL;
        	pQ->tail = NULL;
    	} else {
      		pQ->head = pQ->head->next;
    	}
    	free(old);
    	pQ->size--;
    	return rValue;
}

// adds a new node with data from process to the priority Queue
void PQ_enqueue(priority_Queue* pQ, const Process process) {
	assert(pQ != NULL);
    	Process_node* new = malloc(sizeof(Process_node));
    	assert(new != NULL);
    	new->process = process;
    	new->next = NULL;
    	if (pQ->size == 0) {
       		pQ->head = new;
        	pQ->tail = new;
		pQ->size++;
    	} else {	
		if (process.priority < pQ->head->process.priority) {
			new->next = pQ->head;
			pQ->head = new;
			pQ->size++;	
			return;
		} else {
			for (Process_node* temp = pQ->head; temp->next != NULL; temp = temp->next) {
				if (process.priority < temp->next->process.priority) {
					new->next = temp->next;
					temp->next = new;
					pQ->size++;
					return;
				}
			} 
			pQ->tail->next = new;
			pQ->tail = new;	
			pQ->size++;
		}
    	}	
}

// prints the priority Queue to terminal
void print_PQueue(priority_Queue pQ) {
	printf("\n\t\t\t\t   ===PQueue===\n\n========================================================================================\n");
	if (pQ.size == 0) {
		printf("priority queue is empty");	
		return;
	} else {	
		for(Process_node* temp = pQ.head; temp != NULL; temp = temp->next) {

			printf("pid: %i, Arrival time: %i, Total CPU time: %i, I/O frequency: %i, I/O duration: %i\n\n========================================================================================\n", temp->process.pid, temp->process.arrival_t, temp->process.totalCPU_t, temp->process.io_freq, temp->process.io_dur);
			}
		}	
	return;

}

// free all nodes from the priority Queue
void destroy_PQueue(priority_Queue* pQ) {
	assert(pQ != NULL);

    	while (pQ->head != NULL) {
        	Process_node* del = pQ->head;
        	pQ->head = pQ->head->next; 
		free(del);
    	}

    	pQ->size = 0;
	pQ->tail = NULL;
}

// increments wait time for report 
void incr_wait_time_PQueue(priority_Queue* pQ) {
	assert(pQ != NULL);
 	assert(pQ->size != 0);
 	for(Process_node* temp = pQ->head; temp != NULL; temp = temp->next) {
		temp->process.wait_time++;
		printf("\nready: %i: %i\n", temp->process.pid, temp->process.wait_time);
	}                 
}   
