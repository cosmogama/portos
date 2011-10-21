#ifndef _PRINTFF_H
#define _PRINTFF_H

#include "types.h"

//***************************************************************
// CONSTANTS
//***************************************************************
#define VA_CHAR 'c'
#define VA_SHORT 'o'
#define VA_INT 'i'
#define VA_LONG 'l'
#define VA_FLOAT 'f'
#define VA_DOUBLE 'd'
#define VA_STRING 's'
#define VA_HEX 'h'
#define VA_UINT 'u'

//***************************************************************
// TYPES
//***************************************************************
typedef union va_data{
	char c;
	short sh;
	int i;
	long l;
	float f;
	double d;
	char * s;
	uint32 h;
	uint32 u;
} va_data_t;

//***************************************************************
// PROTOTYPES
//***************************************************************
int printf( const char * format , va_data_t * args );
int printfu( const char * format , uint32 u1 );
int printfuu( const char * format , uint32 u1 , uint32 u2 );

#endif
