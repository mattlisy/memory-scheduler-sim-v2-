/*
	implementation of FCFS schduler algorithm  

*/

#include "FCFS.h" 
#include "process.h"
#include "linked_list.h"
#include "Queue.h"
#include <stdio.h>
#include "io.h"

extern int total_turnaround;
extern int timer; 
extern int processes;

/*
	Admits the process in the new state to the ready state
*/
static void admit(Linked_list* new_list, Queue* ready_queue) {
	int x;
	while(sizeof_Linkedlist(*new_list) != 0 && (x = find_arrival_t(new_list, timer)) != -1) {

		Process temp = pop(new_list, x); 	
		printf("\n ===admit: %i===\n", temp.pid);
		output(temp.pid, "new", "ready"); 
		temp.real_arrival_t = timer;
		enqueue(ready_queue, temp);	
	}	
	return;	
}
/*
	dispatches a process to from ready state to a running state
*/
static void dispatch(Queue* ready_queue, Process* running) {
	if (sizeof_Queue(*ready_queue) == 0) {
		return;
	} else if (isNoProcess(running)){
		*running = dequeue(ready_queue);
		printf("\n ===dispatch: %i===\n", running->pid);	
		output(running->pid, "ready", "running");
	} 
	if (sizeof_Queue(*ready_queue) != 0) {
		incr_wait_time_Queue(ready_queue);
	}
	return; 
}
/*
	io/system event will occur depending on the process io frequency
	Transitions the process from running state to a wait state
*/
static void event(Process* running, Linked_list* wait_list) {
	if (isNoProcess(running)) {
		return;
	} else if(running->elapsed_time % running->io_freq == 0) {
		output(running->pid, "running", "waiting");
		printf("\n === event: %i===\n", running->pid);
		insert_before(wait_list, *running, 0);
		*running = NO_PROCESS;
	} 		
	return;
}

/*
	increments wait time for each process in the wait state
	Transitions process from wait state to ready state when
	io/system event has finished exection
*/
static void event_complete(Linked_list* wait_list, Queue* ready_queue) {

	if (sizeof_Linkedlist(*wait_list) == 0) {	
		return;
	} else {
		incr_time_waited_Linkedlist(wait_list);
		for (int i = 0; i < sizeof_Linkedlist(*wait_list); i++) {
			Process compare_value = get(wait_list, i);
			if (compare_value.time_waited == compare_value.io_dur) {
				output(compare_value.pid, "waiting", "ready");
				printf("\n ===event complete: %i===\n", compare_value.pid);
				Process ready = pop(wait_list, i);
				ready.time_waited = 0;	
				enqueue(ready_queue, ready);	
				i--; // reprocess curr elem; pop shift elems down
			} else {
				printf("\nwaiting: %i: %i\n", compare_value.pid, compare_value.time_waited);
			}
		}
	}
	
	return;
} 


/*
	Terminates a process when program is complete
	Transitions the process from a running state to a terminate state
*/ 
Process terminate(Process* running) {
	Process process_data = NO_PROCESS; 
	if (isNoProcess(running)) {	
		return NO_PROCESS;
	} else if (running->elapsed_time >= running->totalCPU_t) {
		output(running->pid, "running", "terminated");	
		printf("\n ===terminated: %i===\n", running->pid);
		total_turnaround += timer - running->real_arrival_t;
		process_data = *running;
		*running = NO_PROCESS;	
		processes--;
	}
	return process_data;
}

/* 
	simulate FCFS schduler
*/ 
void FCFS(Linked_list* new_list, Process processes_data[], int array_size) {	
	int count = 0;
	Queue ready_queue = create_Queue();
	Process running = NO_PROCESS;
	Linked_list wait_list = create_Linkedlist();		
	
	// sim loop	
	while(processes){

		printf("\ntime: %i\n", timer);
		if (!isNoProcess(&running)) {	
			printf("running: %i: %i\n", running.pid, running.elapsed_time);
		}	

		admit(new_list, &ready_queue);
			
		event_complete(&wait_list, &ready_queue);

			
		Process get = terminate(&running);			
		if (!isNoProcess(&get) && count < array_size){
			processes_data[count++] = get;
		} 

		
		event(&running, &wait_list);
		

		dispatch(&ready_queue, &running);
		if (!isNoProcess(&running)) {	
			running.elapsed_time++;	
		}

		timer++;			
	}	
	destroy_Queue(&ready_queue);
	destroy_Linkedlist(&wait_list);
	printf("\n===< Simulation Complete >===\n");
}
