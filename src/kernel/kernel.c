/***    		** Portos **
*
*  Author: Tony Myers
*  Contact: tonymyers82@gmail.com
*
***/ 

#define RUN_TESTS false

// ********** INCLUDES ********************************
#include "message_printer.h"
#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "PIC.h"
#include "IO.h"
#include "kmalloc_data.h"
#include "process.h"
#include "thread.h"
#include <tests.h>
#include "printf.h"
#include "fs.h"
#include "monitor.h"
#include "kutil.h"
#include "IDE.h"

// ********** CONSTANTS *******************************

// ********** GLOBAL VARIABLES ************************

// ********** PROTOTYPES *****************************

// kernel space initialize functions
void initializeSystem(void);

// user space initialize functions
void setupUserSpace(void);
void setupFileSystem(void);
void startScheduler(void);
void startIdleThread(void);
void startServices(void);
void startShell(void);

// ********** FUNCTIONS ******************************

void kmain( unsigned long mbd_addr , unsigned int magic )
{
   	if ( magic != 0x2BADB002 )
   	{
      /* Something went not according to specs. Print an error */
      /* message and halt, but do *not* rely on the multiboot */
      /* data structure. */

			puts( "magic could not happen here :(\n" );

			return;
   	}

		// message management
		turn_on_error_msgs();
		turn_on_warning_msgs();
		turn_on_info_msgs();
		turn_off_debug_msgs();

		clearMonitor();

		// initialize interrupts
		setupGDT();
		PIC_initialize();
		init_interrupts();	

		// initialize RAM
		init_main_mem( mbd_addr );
		// mbd_addr = 0;

		// run internal tests
		#if RUN_TESTS == true
		run_tests();
		#endif

		// initialize filesystem
		ide_initialize(0x1F0, 0x3F4, 0x170, 0x374, 0x000);
		// ide_detect(0,0,0,0,0,0);
		init_fs();

		// initialize user environment
		setupUserSpace();
	
		// shutdown system
		halt_cpu();
}

void
setupUserSpace(void){	
	setupFileSystem();
	startIdleThread();
	startScheduler();
	startServices();
	startShell();
}

void
setupFileSystem(void){
	
}

void
startIdleThread(void){

}

void
startScheduler(void){

}

void
startServices(void){

}

void
startShell(void){

	puts( "$: "  );

	while( 1 ){ 
  	sleep( 1000 );
  }
}

