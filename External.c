/*
	implementation of FCFS schduler algorithm  

*/

#include "FCFS.h" 
#include "process.h"
#include "linked_list.h"
#include "priority_Queue.h"
#include <stdio.h>
#include "io.h"

extern int timer; 
extern int processes;

/*
	Admits the process in the new state to the ready state
*/
static void EX_admit(Linked_list* new_list, priority_Queue* ready_PQueue) {
	int x;
	while(sizeof_Linkedlist(*new_list) != 0 && (x = find_arrival_t(new_list, timer)) != -1) {

		Process temp = pop(new_list, x); 	
		printf("\n ===admit: %i===\n", temp.pid);
		output(temp.pid, "new", "ready"); 
		PQ_enqueue(ready_PQueue, temp);	
	}	
	return;	
}
/*
	dispatches a process to from ready state to a running state
*/
static void EX_dispatch(priority_Queue* ready_PQueue, Process* running) {
	if (sizeof_PQueue(*ready_PQueue) == 0) {
		return;
	} else if (isNoProcess(running)){
		*running = PQ_dequeue(ready_PQueue);
		printf("\n ===dispatch: %i===\n", running->pid);	
		output(running->pid, "ready", "running");

	}
	return; 
}
/*
	io/system event will occur depending on the process io frequency
	Transitions the process from running state to a wait state
*/
static void EX_event(Process* running, Linked_list* wait_list) {
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
static void EX_event_complete(Linked_list* wait_list, priority_Queue* ready_PQueue) {

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
				PQ_enqueue(ready_PQueue, ready);	
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
static void EX_terminate(Process* running) {
	if (isNoProcess(running)) {	
		return;
	} else if (running->elapsed_time >= running->totalCPU_t) {
		output(running->pid, "running", "terminated");	
		printf("\n ===terminated: %i===\n", running->pid);
		*running = NO_PROCESS;	
		processes--;
	}
	return;
}

/* 
	simulate FCFS schduler
*/ 
void External(Linked_list* new_list) {

	priority_Queue ready_PQueue = create_PQueue();
	Process running = NO_PROCESS;
	Linked_list wait_list = create_Linkedlist();		
	
	// sim loop	
	while(processes){

		printf("\ntime: %i\n", timer);
		if (!isNoProcess(&running)) {	
			printf("running: %i: %i\n", running.pid, running.elapsed_time);
		}	

		EX_admit(new_list, &ready_PQueue);
			
		EX_event_complete(&wait_list, &ready_PQueue);

			
		EX_terminate(&running);			

		
		EX_event(&running, &wait_list);
		

		EX_dispatch(&ready_PQueue, &running);
		if (!isNoProcess(&running)) {	
			running.elapsed_time++;	
		}

		timer++;			
	}	
	destroy_PQueue(&ready_PQueue);
	destroy_Linkedlist(&wait_list);
	printf("\n===< Simulation Complete >===\n");
}
