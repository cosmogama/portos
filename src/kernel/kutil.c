#include "kutil.h"
#include "types.h"

#define asm_halt_cpu() asm volatile("hlt")

BOOL wait_for_user_input_on_halt = TRUE;

// TODO: shouldn't rely on processor speed
void 
sleep( unsigned long milliseconds ){

  const unsigned long STEPS_PER_MILLISEC = 100000;
  unsigned long long iter = STEPS_PER_MILLISEC * milliseconds;
  
  unsigned long long i = 0;
  for(; i<iter; i++){
    i++;
		i--;
	}

}

void wait_for_user_input(void){
	sleep(3000);
}

void halt_cpu(void){
	asm_disable_intr();
	if( wait_for_user_input_on_halt )
		wait_for_user_input();
	asm_halt_cpu();
}

