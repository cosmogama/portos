#include "types.h"

/***
*
*	if err == KEY_NO_ERROR , then check nonPrintableAscii variable
*	otherwise, an error exists.  
* KEY_ERR1: a general keyboard error was detected as scancode 0x00 or 0xFF
* KEY_ERR2: internal failure was detected as scancode 0xFD
* KEY_ERR3: "keyboard fails to acknowledge, please resend" was detected as scancode 0xFE
* KEY_ERR4: scancode not in error, but unrecognized key pressed on keyboard.  This results from unrecognized keyboard models or custom keys.
*
***/
typedef enum KEY_ERROR{
	KEY_NO_ERROR , 
	KEY_ERR1 , 
	KEY_ERR2 , 
	KEY_ERR3 ,
	KEY_ERR4 ,
} KEY_ERROR;

typedef enum KEY_NON_PRINTABLE_ASCII{
	KEY_IS_PRINTABLE_ASCII , 
	KEY_POWER ,
	KEY_VOL_MUTE ,
	KEY_VOL_UP ,
	KEY_VOL_DOWN ,
	KEY_MOUSE_LOCK ,
	KEY_ESC , 
	KEY_F1 , 
	KEY_F2 , 
	KEY_F3 , 
	KEY_F4 , 
  KEY_F5 ,
  KEY_F6 , 
	KEY_F7 ,
	KEY_F8 ,
	KEY_F9 ,
	KEY_F10 ,
	KEY_F11 ,
	KEY_F12 ,
	KEY_INSERT , 
	KEY_DELETE ,
	KEY_NUMLOCK ,
	KEY_SCROLLLOCK ,
	KEY_PRTSC ,
	KEY_PAUSE ,
	KEY_CAPS ,
	KEY_ENTER ,
	KEY_SHIFT_L , 
	KEY_SHIFT_R ,
	KEY_FN ,
	KEY_CTRL_L ,
	KEY_WIN ,
	KEY_ALT_L ,
	KEY_ALT_R ,
	KEY_MENU ,
	KEY_CTRL_R ,
	KEY_PGUP ,
	KEY_PGDN ,
	KEY_UP ,
	KEY_LEFT ,
	KEY_RIGHT ,
	KEY_DOWN ,
	KEY_SHIFT ,
	KEY_MOUSE_LEFT ,
	KEY_MOUSE_RIGHT 
} KEY_NON_PRINTABLE_ASCII;

typedef enum KEY_EVENT{
	KEY_EVENT_UP ,
	KEY_EVENT_DOWN
} KEY_EVENT;

/***
*
*	Key pressed will be stored in the alphaNumeric variable unless either of 2 cases are valid
* 1) there was an error associated with this kepress.  In this case, the KEY_ERR will be set to a non KEY_NO_ERROR value.
* 2) the key pressed was a non-alpha numeric key, ie shift was pressed.  In this case the KEY_NON_ALPHANUMERIC variable will be set 
*		 to a non KEY_IS_ALPHANUMERIC value.  Additionally in this case, disregard the alphaNumeric variable and use KEY_NON_ALPHANUMERIC value.
*	
***/
typedef struct KEY{
	uint8 printableAscii;
	KEY_NON_PRINTABLE_ASCII nonPrintableAscii;
	KEY_ERROR err;
	KEY_EVENT event;
} KEY;

// ***************************************************
// FUNCTIONS
// ***************************************************
void decodeKey( KEY * key , uint8 scancode );


