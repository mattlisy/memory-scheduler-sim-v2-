#include "linked_list.h"
#include "process.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>



#define BUFFER_SIZE 128		// buffer to read file
				
extern int processes;
extern int timer;

/*
	Takes data csv provides and creates processes from them. 
	Each process is added to a linked list. 
	Linked list is returned represent a data structure for the new state
*/ 
Linked_list input(char** file) { 
	// print file name
	printf("file: %s\n", *file);
	// open file
	FILE *data = fopen(*file, "r");
	if (data == NULL) { 
		perror("error opening file");
		exit(0);
	}
	
	Linked_list new_list = create_Linkedlist();
	char buffer[BUFFER_SIZE];
	int first_iteration = 1; // flag to skip headers of CSV
	while (fgets(buffer, BUFFER_SIZE, data)) { 
		
		// skip headers
		if (first_iteration) {
			first_iteration = 0;
			continue;
		}
		Process new;	

		// fill new process 	
		new.pid = atoi(strtok(buffer, ","));
		new.arrival_t = atoi(strtok(NULL, ","));
		new.totalCPU_t = atoi(strtok(NULL, ","));
		new.io_freq = atoi(strtok(NULL, ","));
		new.io_dur = atoi(strtok(NULL, ","));	
		new.elapsed_time = 0;
		new.time_waited = 0;
		new.priority = atoi(strtok(NULL, ","));
		new.memory_req = atoi(strtok(NULL, ","));
		new.memory_seg = 0;


		// add process to new
		insert_before(&new_list, new, 0);
		processes++;	
	} 
	fclose(data);	
	return new_list;
}



/*
	Simulator Output to file
*/
void output(const int pid, const char* old_state, const char* new_state) {
	time_t now = time(NULL);
	char filename[50];
	struct tm* timeinfo = localtime(&now);
	strftime(filename, sizeof(filename), "Simulator-Output-%Y%m%d%H%M%S.txt", timeinfo);
  
	FILE* out_file = fopen(filename, "a");
	if (out_file == NULL) {
		perror("error opening output file");
	} 
	fprintf(out_file, "time: %i, pid: %i, old state: %s, new_state: %s\n\n", timer, pid, old_state, new_state);
	fclose(out_file);	
}
	
