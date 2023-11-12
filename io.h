#ifndef IO_H
#define IO_H
#include "linked_list.h"

Linked_list input(char** file); 

void output(const int pid, const char* old_state, const char* new_state);


#endif 
