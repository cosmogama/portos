#include "process.h"

int cur_pid = 0;

int new_pid();

struct process{
	int pid;
};

void exec(){
  int pid = new_pid();
	pid = pid;
}

void fork(){
  
}

int new_pid(){
	return ++cur_pid;
}
