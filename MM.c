/*
	implementation of FCFS schduler algorithm with memory

*/
#include "MM.h"
#include "FCFS.h" 
#include "process.h"
#include "linked_list.h"
#include "Queue.h"
#include <stdio.h>
#include "io.h"
#include <stdlib.h>

extern int timer; 
extern int processes;

static int check_available_memory(Process process, const Memory memory) {
	for(int i = 0; i < 4; i++) {
		if (memory[i].available == 0 && process.memory_req <= memory[i].size) {
			return i;	
		}
	}		
	return -1;
}

/*
	Admits the process in the new state to the ready state
*/
static void MM_admit(Linked_list* new_list, Queue* ready_queue, Memory memory) {
	int x;
	while(sizeof_Linkedlist(*new_list) != 0 && (x = find_arrival_t(new_list, timer)) != -1) {
		
		int seg_num = check_available_memory(get(new_list, x), memory);	 
		if(seg_num == -1) {
			return;
		} else {
			Process temp = pop(new_list, x); 		
			temp.memory_seg = seg_num;	
			memory[seg_num].available = 1;
			printf("\n ===admit: %i===\n", temp.pid);
			output(temp.pid, "new", "ready"); 
			enqueue(ready_queue, temp);	
		}
	}	
	return;	
}
/*
	dispatches a process to from ready state to a running state
*/
static void MM_dispatch(Queue* ready_queue, Process* running) {
	if (sizeof_Queue(*ready_queue) == 0) {
		return;
	} else if (isNoProcess(running)){
		*running = dequeue(ready_queue);
		printf("\n ===dispatch: %i===\n", running->pid);	
		output(running->pid, "ready", "running");

	}
	return; 
}
/*
	io/system event will occur depending on the process io frequency
	Transitions the process from running state to a wait state
*/
static void MM_event(Process* running, Linked_list* wait_list) {
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
static void MM_event_complete(Linked_list* wait_list, Queue* ready_queue) {

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
static void MM_terminate(Process* running, Memory memory) {
	if (isNoProcess(running)) {	
		return;
	} else if (running->elapsed_time >= running->totalCPU_t) {
		//release memory 
		memory[running->memory_seg].available = 0; 

		output(running->pid, "running", "terminated");	
		printf("\n ===terminated: %i===\n", running->pid);
		*running = NO_PROCESS;	
		processes--;
	}
	return;
}

int compareSegments(const void* a, const void* b) {
	const Segment* cmp1 = (Segment*) a;
	const Segment* cmp2 = (Segment*) b;

	
	return cmp1->size - cmp2->size;
}	

void add_memory_segs(Memory memory, int seg_a, int seg_b, int seg_c, int seg_d) {
		
	if (seg_a + seg_b + seg_c + seg_d > 1000) {
		printf("Error: segments over 1GB\n");
		exit(1);
	}
			
	memory[0] = (Segment){seg_a, 0};
	memory[1] = (Segment){seg_b, 0};
	memory[2] = (Segment){seg_c, 0};
	memory[3] = (Segment){seg_d, 0};

	qsort(memory, 4, sizeof(memory[0]), compareSegments); 
}

/* 
	simulate FCFS schduler
*/ 
void Memory_Mangement(Linked_list* new_list, Memory memory) {

	Queue ready_queue = create_Queue();
	Process running = NO_PROCESS;
	Linked_list wait_list = create_Linkedlist();		
	
	// sim loop	
	while(processes){

		printf("\ntime: %i\n", timer);
		if (!isNoProcess(&running)) {	
			printf("running: %i: %i\n", running.pid, running.elapsed_time);
		}	

		MM_admit(new_list, &ready_queue, memory);
			
		MM_event_complete(&wait_list, &ready_queue);

			
		MM_terminate(&running, memory);			

		
		MM_event(&running, &wait_list);
		

		MM_dispatch(&ready_queue, &running);
		if (!isNoProcess(&running)) {	
			running.elapsed_time++;	
		}

		timer++;			
	}	
	destroy_Queue(&ready_queue);
	destroy_Linkedlist(&wait_list);
	printf("\n===< Simulation Complete >===\n");
}
