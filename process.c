#include "process.h"
#include <stdbool.h>
/*
	Checks to see if a process does not exist
	returns a bool to represent this; 1 if y; 0 if n
*/
bool isNoProcess(Process* process) {
	return (process->pid == -1 &&
        	process->arrival_t == -1 &&
 	        process->totalCPU_t == -1 &&
             	process->io_freq == -1 &&
             	process->io_dur == -1 &&
            	process->elapsed_time == -1 && process->time_waited == -1);
}
