#ifndef _PRINTF_H
#define _PRINTF_H

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
// PROTOTYPES
//***************************************************************
int printf( const char * format , ... );
int sprintf( char * out , const char * format , ... );

#endif
