#ifndef __DATA_H
#define __DATA_H

#include "types.h"

//*****************************************************
// TYPES
//*****************************************************

typedef enum BASE{
	BINARY ,
	DECIMAL ,
	HEX
} BASE;

typedef struct BYTE_HEX{
	char hi;
	char lo;
} BYTE_HEX;

//*****************************************************
// FUNCTIONS
//*****************************************************

void hbtoa( BYTE_HEX * dest , uint8 src );
void itoa( char (* dest)[11] , int src );
void uitoa( char (* dest)[11] , uint32 src );
void ltoa(char (* dest)[20] ,long value);
void ultoa(char (* dest)[20] ,unsigned long value);
void ustoa( char (* dest)[6] , uint16 src );

void uitoh( char (* dest)[11] , uint32 src );

#endif
