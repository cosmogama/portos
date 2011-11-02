#ifndef _PRINTF_H
#define _PRINTF_H

#include "types.h"

//***************************************************************
// CONSTANTS
//***************************************************************
#define VA_BYTE 'b'
#define VA_CHAR 'c'
#define VA_SHORT 'o'
#define VA_INT 'i'
#define VA_LONG 'l'
#define VA_INT64 'j'
#define VA_FLOAT 'f'
#define VA_DOUBLE 'd'

#define VA_UNSIGNED 'u'

#define VA_STRING 's'
#define VA_HEX 'h'

//***************************************************************
// PROTOTYPES
//***************************************************************
int printf( const char * format , ... );
int sprintf( char * out , const char * format , ... );

// internal testing
int print( char ** out , int * varg );
char * print_arg( char ** out , BOOL is_unsigned , char format_specifier , int * varg );

#endif
