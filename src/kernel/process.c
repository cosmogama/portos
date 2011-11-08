#include "process.h"

int cur_pid = 0;

int new_pid(void);

struct process{
	int pid;
};

void exec(void){
  int pid = new_pid();
	pid = pid;
}

void fork(void){
  
}

int new_pid(void){
	return ++cur_pid;
}
