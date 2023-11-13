#ifndef MM_H 
#define MM_H
#include "linked_list.h"
#include <stdbool.h>

typedef struct {
	int size;
	bool available;
} Segment;

typedef Segment Memory[4];

/*
	init memory segs 
*/
void add_memory_segs(Memory memory, int seg_a, int seg_b, int seg_c, int seg_d);

/*
	implementation of FCFS schedeuler algorithm  
*/
void Memory_Mangement(Linked_list* new_list, Memory memory, Process processes_data[], int array_size);

#endif 
