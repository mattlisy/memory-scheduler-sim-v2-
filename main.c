/*
Matthew Lisy 101231092 
Kyle Taticek 101193550

TODO:
	- add more output
	- add system metrics 	
	- testing 
*/

#include "MM.h"
#include "RR.h"
#include "priority_Queue.h"
#include "External.h"
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
int total_turnaround = 0;

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



int main(int agrc, char* agrv[]) {
	//data structures 
	Linked_list new_list;	
	Memory memory;
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
											      				
			if (i + 4 > agrc) {
				printf("Error: not enough arguments\n");
				exit(1);
			}
			mode = MM;
			add_memory_segs(memory, atoi(agrv[i+1]), atoi(agrv[i+2]), atoi(agrv[i+3]), atoi(agrv[i+4]));	
			i += 4;
		} else {
			printf("\n%s is not a command\n", agrv[i]);
			return EXIT_FAILURE;

		}		
	}
			
	// check input file 
	if (sizeof_Linkedlist(new_list) == 0) {
		printf("Error: no input file\n");
		return EXIT_FAILURE;
	} 		
	// save max processes before sim 
	int total_processes = processes;	
	Process processes_data[total_processes];
	// call mode 
	switch(mode) {
		
		case FS: FCFS(&new_list, processes_data, total_processes); 
			 break;
		case EX: External(&new_list, processes_data, total_processes);
			 break;
		case RR: Round_Robin(&new_list, processes_data, total_processes);  
			 break;	
		case MM: Memory_Mangement(&new_list, memory, processes_data, total_processes);
			 break;

	}
	timer--; // final loop checks processes must represent data properly
	// report of sim
	double throughput = (double)total_processes / (double)timer; 	
	double avg_turnaround = (double)total_turnaround / (double)total_processes;   
	char buffer[64];
	for(int i = 0; i < total_processes; i++) {
		printf("(pid: %i, wait time: %i) ", processes_data[i].pid, processes_data[i].wait_time);
	}
	
	sprintf(buffer, "\nReport\n\tthroughput: %f\n\taverage turn around: %f\n", throughput, avg_turnaround);
	printf("%s", buffer);
}
