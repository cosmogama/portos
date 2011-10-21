#include "keyboard.h"

// **********************************************************
//	DEFINES
// **********************************************************

#define KEY_EVENT_UP_OFFSET 80

// **********************************************************
//	FUNCTIONS 
// **********************************************************

void
decodeKey( KEY * key , uint8 scancode ){
	
	// initialize KEY to default values
	key->printableAscii = 'A';
	key->nonPrintableAscii = KEY_IS_PRINTABLE_ASCII; 
	key->err = KEY_NO_ERROR;
	key->event = KEY_EVENT_DOWN;
	
	// error ?
	//if( scancode != 0xFA ){
		if( scancode == 0x00 || scancode == 0xFF ){
			key->err = KEY_ERR1; 
			return;
		}
		else if( scancode == 0xFD ){
			key->err = KEY_ERR2;
			return;
		}
		else if( scancode == 0xFE ){
			key->err = KEY_ERR3;
			return;
		}
	//}

	// ignore key-ups for now
	if( scancode >= KEY_EVENT_UP_OFFSET ){
		key->event = KEY_EVENT_UP;
		return;
	}

	// non-printableAscii ?
	if( scancode == 0x01 ){ key->nonPrintableAscii = KEY_ESC; return; }
	if( scancode == 0x1C ){ key->nonPrintableAscii = KEY_ENTER; return; }
	if( scancode == 0x1D ){ key->nonPrintableAscii = KEY_CTRL_L; return; }
	if( scancode == 0x2A ){ key->nonPrintableAscii = KEY_SHIFT_L; return; }
	if( scancode == 0x36 ){ key->nonPrintableAscii = KEY_SHIFT_R; return; }
	if( scancode == 0x37 ){ key->nonPrintableAscii = KEY_PRTSC; return; }
	if( scancode == 0x38 ){ key->nonPrintableAscii = KEY_ALT_L; return; }
	if( scancode == 0x3A ){ key->nonPrintableAscii = KEY_CAPS; return; }	
	if( scancode == 0x3B ){ key->nonPrintableAscii = KEY_F1; return; }
	if( scancode == 0x3C ){ key->nonPrintableAscii = KEY_F2; return; }
	if( scancode == 0x3D ){ key->nonPrintableAscii = KEY_F3; return; }
	if( scancode == 0x3E ){ key->nonPrintableAscii = KEY_F4; return; }
	if( scancode == 0x3F ){ key->nonPrintableAscii = KEY_F5; return; }
	if( scancode == 0x40 ){ key->nonPrintableAscii = KEY_F6; return; }
	if( scancode == 0x41 ){ key->nonPrintableAscii = KEY_F7; return; }
	if( scancode == 0x42 ){ key->nonPrintableAscii = KEY_F8; return; }
	if( scancode == 0x43 ){ key->nonPrintableAscii = KEY_F9; return; }
	if( scancode == 0x44 ){ key->nonPrintableAscii = KEY_F10; return; }
	if( scancode == 0x45 ){ key->nonPrintableAscii = KEY_NUMLOCK; return; }
	if( scancode == 0x46 ){ key->nonPrintableAscii = KEY_SCROLLLOCK; return; }
	if( scancode == 0x48 ){ key->nonPrintableAscii = KEY_UP; return; }
	if( scancode == 0x49 ){ key->nonPrintableAscii = KEY_PGUP; return; }
	if( scancode == 0x4B ){ key->nonPrintableAscii = KEY_LEFT; return; }
	if( scancode == 0x4D ){ key->nonPrintableAscii = KEY_RIGHT; return; }
	if( scancode == 0x50 ){ key->nonPrintableAscii = KEY_DOWN; return; }	
	if( scancode == 0x51 ){ key->nonPrintableAscii = KEY_PGDN; return; }
	if( scancode == 0x57 ){ key->nonPrintableAscii = KEY_F11; return; }
	if( scancode == 0x58 ){ key->nonPrintableAscii = KEY_F12; return; }

	// printable ascii character
	if( scancode >= 0x02 && scancode <=0x0A ){ key->printableAscii = scancode + 47; return; }
	if( scancode == 0x0B )						{ key->printableAscii = '0'; return; }
	if( scancode == 0x0C )						{ key->printableAscii = '-'; return; }
	if( scancode == 0x0D )						{ key->printableAscii = '='; return; }
	if( scancode == 0x0E )						{ key->printableAscii = 8; return; }
	if( scancode == 0x0F )						{ key->printableAscii = 9; return; }
	if( scancode == 0x10 )						{ key->printableAscii = 'q'; return; }
	if( scancode == 0x11 )						{ key->printableAscii = 'w'; return; }
	if( scancode == 0x12 )						{ key->printableAscii = 'e'; return; }
	if( scancode == 0x13 )						{ key->printableAscii = 'r'; return; }
	if( scancode == 0x14 )						{ key->printableAscii = 't'; return; }
	if( scancode == 0x15 )						{ key->printableAscii = 'y'; return; }
	if( scancode == 0x16 )						{ key->printableAscii = 'u'; return; }
	if( scancode == 0x17 )						{ key->printableAscii = 'i'; return; }
	if( scancode == 0x18 )						{ key->printableAscii = 'o'; return; }
	if( scancode == 0x19 )						{ key->printableAscii = 'p'; return; }
	if( scancode == 0x1A )						{ key->printableAscii = '['; return; }
	if( scancode == 0x1B )						{ key->printableAscii = ']'; return; }
	if( scancode == 0x1E )						{ key->printableAscii = 'a'; return; }
	if( scancode == 0x1F )						{ key->printableAscii = 's'; return; }
	if( scancode == 0x20 )						{ key->printableAscii = 'd'; return; }
	if( scancode == 0x21 )						{ key->printableAscii = 'f'; return; }
	if( scancode == 0x22 )						{ key->printableAscii = 'g'; return; }
	if( scancode == 0x23 )						{ key->printableAscii = 'h'; return; }
	if( scancode == 0x24 )						{ key->printableAscii = 'j'; return; }
	if( scancode == 0x25 )						{ key->printableAscii = 'k'; return; }
	if( scancode == 0x26 )						{ key->printableAscii = 'l'; return; }
	if( scancode == 0x27 )						{ key->printableAscii = ';'; return; }
	if( scancode == 0x28 )						{ key->printableAscii = '\''; return; }
	if( scancode == 0x29 )						{ key->printableAscii = '`'; return; }
	if( scancode == 0x2B )						{ key->printableAscii = '\\'; return; }
	if( scancode == 0x2C )						{ key->printableAscii = 'z'; return; }
	if( scancode == 0x2D )						{ key->printableAscii = 'x'; return; }
	if( scancode == 0x2E )						{ key->printableAscii = 'c'; return; }
	if( scancode == 0x2F )						{ key->printableAscii = 'v'; return; }
	if( scancode == 0x30 )						{ key->printableAscii = 'b'; return; }
	if( scancode == 0x31 )						{ key->printableAscii = 'n'; return; }
	if( scancode == 0x32 )						{ key->printableAscii = 'm'; return; }
	if( scancode == 0x33 )						{ key->printableAscii = ','; return; }
	if( scancode == 0x34 )						{ key->printableAscii = '.'; return; }
	if( scancode == 0x35 )						{ key->printableAscii = '/'; return; }
  if( scancode == 0x39 )						{ key->printableAscii = ' '; return; }

	// unrecognized key detected
	key->err = KEY_ERR4;

	return;
}	

