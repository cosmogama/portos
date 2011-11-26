/***    		** Portos **
*
*  Author: Tony Myers
*  Contact: tonymyers82@gmail.com
*
***/ 

// #define RUN_TESTS

// ********** INCLUDES ********************************

#ifdef RUN_TESTS
	#include "tests.h"
#endif

#include "message_printer.h"
#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "PIC.h"
#include "IO.h"
#include "kmalloc_data.h"
#include "process.h"
#include "thread.h"
#include "printf.h"
#include "fs.h"
#include "monitor.h"
#include "kutil.h"
#include "IDE.h"

// ********** CONSTANTS *******************************

// ********** GLOBAL VARIABLES ************************

// ********** PROTOTYPES *****************************

// kernel space initialize functions
void initialize_system(void);

// user space initialize functions
void setup_user_space(void);
void setup_file_system(void);
void start_scheduler(void);
void start_idle_thread(void);
void start_services(void);
void start_shell(void);

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

		// initialize IDE
		ide_initialize(0x1F0, 0x3F4, 0x170, 0x374, 0x000);

		// run internal tests
		#ifdef RUN_TESTS
			run_tests();
		#endif

		// initialize filesystem
		init_fs();

// 		spawn_thread();

		// initialize user environment
		setup_user_space();
	
		// shutdown system
		halt_cpu();
}

void
setup_user_space(void){	
	setup_file_system();
	start_idle_thread();
	start_scheduler();
	start_services();
	start_shell();
}

void
setup_file_system(void){
	
}

void
start_idle_thread(void){

}

void
start_scheduler(void){

}

void
start_services(void){

}

void
start_shell(void){

	puts( "$: "  );

	while( 1 ){ 
  	sleep( 1000 );
  }
}

