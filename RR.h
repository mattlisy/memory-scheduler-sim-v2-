#ifndef RR_H 
#define RR_H
#include "linked_list.h"
#include "Queue.h" 

/*
	implementation of FCFS schedeuler algorithm  
*/
void Round_Robin(Linked_list* new_list, Process wait_time_data[], int array_size);

#endif 
