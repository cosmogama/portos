#include "interrupts.h"
#include "keyboard.h"
#include "idt.h"
#include "PIC.h"
#include "IO.h"
#include "monitor.h"
#include "data.h"

// **************************************************
//	PROTOTYPES
// **************************************************

/* here are references to all the isr stubs that are defined in isr_stubs.s */
extern void isr_stub(void);
extern void isr_stub_kbd(void);

// **************************************************
//	TYPES
// **************************************************

typedef void (*interrupt_t)(void);

// **************************************************
//	GLOBAL DATA
// **************************************************

/* table of the body of the interrupt handlers */
interrupt_t interrupt_handlers[MAX_INTERRUPTS];

// **************************************************
//	INTERRUPT SERVICE ROUTINES
// **************************************************

void handle_interrupt(void){
	outportb(0x20,0x20);
}

void handle_interrupt_kbd(void){

	// receive key press from PIC
	unsigned char scancode = inportb(0x60);

	// interpret key press
	KEY key;
	decodeKey( &key , scancode );

	if( key.err != KEY_NO_ERROR ){
		puts( "invalid key press or error reading key press\0" );
		putb( scancode );
		// tell PIC we are done receiving key press
		outportb(0x20,0x20);
		return;
	}
	
	if( key.event == KEY_EVENT_UP ){
		//puts( "key up for scancode=" );
		//putb( scancode );
	}
	else if( key.nonPrintableAscii != KEY_IS_PRINTABLE_ASCII ){
		puts( "non printable ascii key\0" );
	}else{
		
		//putc( '!' );
		putc( key.printableAscii );
		/*putc( '-' );
		putb( key.nonPrintableAscii );
		putc( '-' );
		putb( key.err );
		putc( '-' );
		putb( key.event );
		putc( '-' );
		putb( scancode );
		putc( '!' );
		*/
	}
	
	// tell PIC we are done receiving key press
	outportb(0x20,0x20);
}

// **************************************************
//	UTILITY FUNCTIONS
// **************************************************

void register_isr(int no, interrupt_t i) {
  interrupt_handlers[no] = i;
}

void init_interrupts(void) {

  // setup desciptor table
  init_IDT();

	//int i;
  //for(i = 0; i < MAX_INTERRUPTS; ++i) 
  //  interrupt_handlers[i] = dummy_handler;
  
}

