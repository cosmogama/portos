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

char * btoa( char * dest , BYTE src , BOOL is_unsigned );
char * shtoa( char * dest , short src , BOOL is_unsigned );
char * itoa( char * dest , int src , BOOL is_unsigned );
char * ltoa( char * dest ,long value , BOOL is_unsigned );
char * i64toa( char * dest , int64 value , BOOL is_unsigned );

char * ftoa( char * dest , float value);
char * dtoa( char * dest , double value);

char * uitoh( char * dest , uint32 src );
void hbtoa( BYTE_HEX * dest , uint8 src );

#endif
