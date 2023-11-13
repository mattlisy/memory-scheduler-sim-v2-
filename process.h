#ifndef PROCESS_H
#define PROCESS_H

#include <stdbool.h>

#define NO_PROCESS (Process){-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}  // represents a process that does not exist
// type defintion for Process 
typedef struct {
	int pid; 
	int arrival_t; 
	int totalCPU_t;
	int io_freq;
	int io_dur;
	int elapsed_time;
	int time_waited;
	int priority;
	int memory_req;
	int memory_seg;
} Process;

// type defintion for Process_node to be used in data structures
typedef struct Process_node {
	Process process;
	struct Process_node* next;
} Process_node;

bool isNoProcess(Process* process);

#endif 
