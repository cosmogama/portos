/***    		** PortalOS **
*
*  Author: Tony Myers
*  Contact: tonymyers82@gmail.com
*
***/ 

// ********** INCLUDES ********************************
#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "PIC.h"
#include "monitor.h"
#include "IO.h"
#include "kmalloc.h"
#include "kmalloc_data.h"
#include "process.h"
#include "thread.h"
#include "tests.h"

// ********** CONSTANTS *******************************

// ********** GLOBAL VARIABLES ************************

// ********** PROTOTYPES *****************************

// kernel space initialize functions
void initializeSystem();
void shutdownSystem();

// user space initialize functions
void setupUserSpace();
void setupFileSystem();
void startScheduler();
void startIdleThread();
void startServices();
void startShell();

// utiltity functions
void sleep( unsigned long milliseconds );

// ********** FUNCTIONS ******************************

void kmain( unsigned long mbd_addr , unsigned int magic )
{
   	if ( magic != 0x2BADB002 )
   	{
      /* Something went not according to specs. Print an error */
      /* message and halt, but do *not* rely on the multiboot */
      /* data structure. */

			puts( "magic could not happen here :(" );

			return;
   	}

		// initialize kernel environment
		clearMonitor();
		//init_main_mem( mbd_addr );		
		mbd_addr = NULL;
		setupGDT();
		PIC_initialize();
		init_interrupts();	

		// tests
		//test_sanity();
		test_malloc_free();

		// initialize user environment
		setupUserSpace();
	
		// shutdown system
		shutdownSystem();
}

void
shutdownSystem(){
	asm( "hlt" );
}

void
setupUserSpace(){	
	setupFileSystem();
	startIdleThread();
	startScheduler();
	startServices();
	startShell();
}

void
setupFileSystem(){
	
}

void
startIdleThread(){

}

void
startScheduler(){

}

void
startServices(){

}

void
startShell(){

	puts( "$: \0"  );

	while( 1 ){ 
  	sleep( 1000 );
  }
}

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

