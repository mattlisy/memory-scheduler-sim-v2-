/*
Matthew Lisy 101231092 
Kyle Taticek 101193550

TODO:
	* PART 1 *

	x implement FCFS non-preemption test with 
		x file organization
	- implement external priorities no premption scheduler 
	- implement round robin with 1s timeout 

	* PART 2 *
	- add memory dependencies 1GB with 4 partitions -> partition will vary in size 

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "FCFS.h"
#include "Queue.h"
#include "linked_list.h"
#include "process.h"
#include "io.h"

#define BUFFER_SIZE 64 		// buffer to read file
#define START_TIME 0 		// sim start time

enum modes {
	FS,
	EX,
	RR,
	MM
};

int mode = FS; // default mode = FCFS  
int timer = START_TIME;
int processes = 0;

/*
CLI FLAGS 

-i --input : input file
-F --FCFS : FCFS schduler
-E --EXTERNAL : External scheduler
-R -ROUND_ROBIN : RR schduler
-M --MEMORY_MANGEMENT : FCFS scheduler with memory  
*/
void help(void) { 
	
	printf("Commands:\n\t-i / --input \"file.csv : file input in csv format\"\n");
	printf("\t-F / --FCFS : use FCFS scheduler\n");
	printf("\t-E / --EXTERNAL : use External scheduler\n");
	printf("\t-R / --ROUND_ROBIN : use RR scheduler\n");
	printf("\t-M / --MEMORY_MANGEMENT int int int int : implements memory in FCFS scheduler\n");  
	
}


/*	-> RR 

void interrupt(Process* running, Queue* ready_queue) {
	if (isNoProcess(running)) {
		return;
	}else if (running->elapsed_time % INTERRUPT_FREQ == 0) {
		Output(running->pid, "ready", "interrupt");
		printf("\n===interrupt: %i===\n", running->pid);
		enqueue(ready_queue, *running);
		*running = NO_PROCESS;
	}
	
	return;

}	

*/


void Round_Robin() {

	printf("not implemented\n");
}

void Memory_Mangement() {

	printf("not implemented\n");

}
int main(int agrc, char* agrv[]) {
	
	//data structures 	
	Linked_list new_list;	

	// commands
	if (agrc < 2) {
		printf("Error: no commands supplied\n");
		return EXIT_FAILURE;
	}	

	// setting flags 	
	for (int i = 1; i < agrc; i++) { 
		if ((strcmp(agrv[i], "-h") == 0) || (strcmp(agrv[i], "--help") == 0)) {
		
			help();
			return EXIT_SUCCESS; // help cannot be used with other flags 

		} else if ((strcmp(agrv[i], "-i") == 0) || (strcmp(agrv[i],"--input") == 0)) {  // -i for input file

			new_list = input(&agrv[++i]);	

		} else if ((strcmp(agrv[i], "-F") == 0) || (strcmp(agrv[i],"--FCFS") == 0)) { // -F for FCFS schduler

			mode = FS;

		} else if ((strcmp(agrv[i], "-E") == 0) || (strcmp(agrv[i],"--EXTERNAL") == 0)) { // -F for FCFS schduler
			
			mode = EX;			
	
		} else if ((strcmp(agrv[i], "-R") == 0) || (strcmp(agrv[i],"--ROUND_ROBIN") == 0)) { // -F for FCFS schduler
											      
			mode = RR; 
											   
		} else if ((strcmp(agrv[i], "-M") == 0) || (strcmp(agrv[i],"--MEMORY_MANGEMENT") == 0)) { // -F for FCFS schduler
											      				
			mode = MM;
			

		} else {
			printf("\n%s is not a command\n", agrv[i]);
			return EXIT_FAILURE;

		}		
	}
		
	if (sizeof_Linkedlist(new_list) == 0) {
		printf("\ninput file error\n");
		return EXIT_FAILURE;
	} 		
	// call mode 
	switch(mode) {
		
		case FS: FCFS(&new_list); 
			 break;
		case EX: External();
			 break;
		case RR: Round_Robin();  
			 break;	
		case MM: Memory_Mangement();
			 break;

	}
	
}
