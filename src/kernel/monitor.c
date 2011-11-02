#include "IO.h"
#include "data.h"
#include "monitor.h"
#include "message_printer.h"

#define CX_MAX 80
#define CY_MAX 250
#define NUM_PIXELS ( CX_MAX * CY_MAX )

//**************************************************
//	GLOBALS
//**************************************************

int cx = 0 , cy = 0;

//**************************************************
//	PROTOTYPES
//**************************************************

void repaint_cursor();
uint16 cursor_forward();
uint16 cursor_back();

// ***********************************************************************
//
//			CONSOLE OUTPUT PRINT FUNCTIONS
//
// ***********************************************************************

void putc( const char c  ){

	volatile unsigned char *videoram = (volatile unsigned char *) 0xb8000;

	if( c == '\n' || c == '\r' ){
		cx = 0;
		cy++;
		repaint_cursor();
		return;
	}
		
	unsigned short position=(cy*80) + cx;

  videoram[ 2*position ] = c;
	videoram[ 1 + 2*position ] = 0x07;
	
	cursor_forward();

	repaint_cursor();
}

void putb( const BYTE b ){

	BYTE_HEX bh;
	hbtoa( &bh , b );

	putc( '0' );
	putc( 'x' );
	putc( bh.hi );
	putc( bh.lo );
}

char * puts( const char * string  ){
	
	volatile unsigned char *videoram = (unsigned char *) 0xb8000;  

	unsigned short position=(cy*80) + cx;
  int i = 0;
  while( string[i] != '\0' ){

		if( string[i] == '\n' || string[i] == '\r' ){
			cx = 0;
			cy++;
			position=(cy*80) + cx;
			i++;
			continue;
		}

    videoram[ 2*position ] = string[i++];
    videoram[ 1 + 2*position ] = 0x07;
    position = cursor_forward();
  }

	repaint_cursor();

	return (char *) string + i;
}

// ********************************************************************
//
//			MONITOR UTILITY FUNCTIONS
//
// ********************************************************************

void clearMonitor(){

	volatile unsigned char *videoram = (unsigned char *) 0xb8000;

  int i = 0;  
  for(;i<NUM_PIXELS;i++){
    videoram[ 2*i ] = 0x00;
    videoram[ 1 + 2*i ] = 0x07;
  }
}

void repaint_cursor()
{
    unsigned short position=(cy*80) + cx;
 
    // cursor LOW port to vga INDEX register
    outportb(0x3D4, 0x0F);
    outportb(0x3D5, (unsigned char)(position&0xFF));
    // cursor HIGH port to vga INDEX register
    outportb(0x3D4, 0x0E);
    outportb(0x3D5, (unsigned char )((position>>8)&0xFF));
}

void backspace(){

		volatile unsigned char *videoram = (unsigned char *) 0xb8000;  
		unsigned short position = position=(cy*80) + cx;

		// clear current character
		videoram[ 2*position ] = ' ';
    videoram[ 1 + 2*position ] = 0x07;

		position = cursor_back();

		repaint_cursor();
}

uint16 
cursor_forward(){
	cx++;
  if( cx == CX_MAX ){
  	cx = 0;
    if( cy != CY_MAX ) cy++;
  }
	return cy * CX_MAX + cx;
}

uint16 
cursor_back(){
	cx--;
  if( cx == 0 ){
  	cx = CX_MAX;
    if( cy != 0 ) cy--;
  }
	return cy * CX_MAX + cx;
}
