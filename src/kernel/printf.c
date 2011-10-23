#include "printf.h"
#include "monitor.h"
#include "types.h"

//***************************************************************
// PROTOTYPES
//***************************************************************
void print_arg( char format_specifier , int * varg );
int print( char ** out , int * varg );

//***************************************************************
// FUNCTIONS
//***************************************************************
int printf( const char * format , ... ){
	int *varg = (int *)(&format);
	return print( NULL , varg );
}

int sprintf( char * out , const char * format , ... ){
	int *varg = (int *)(&format);
	return print( &out , varg );
}

int print( char ** out , int * varg ){
	// TODO: write to out buffer for sprintf instead of stdout
	out = NULL; 

	const char * format = (char *)(*varg++);

	int c = 0;
	while( format[c] != '\0' ){
		switch( format[c] ){
			case '%': print_arg( format[++c] , varg ); break;
			default: putc( format[c] ); break;
		}
		c++;
	}

	return 0;
}

void print_arg( char format_specifier , int * varg ){
	if( format_specifier == 'c' )
		putc((char)(*varg++));
	else if( format_specifier == VA_SHORT )
		putsh((short)(*varg++));
	else if( format_specifier == VA_INT )
		puti((int)(*varg++));
	else if( format_specifier == VA_LONG )
		putl((long)(*varg++));
	else if( format_specifier == VA_FLOAT )
		putf((float)(*varg++));
	else if( format_specifier == VA_DOUBLE )
		putd((double)(*varg++));
	else if( format_specifier == VA_STRING )
		puts((char *)(*varg++));
	else if( format_specifier == VA_HEX )
		puth((uint32)(*varg++));
	else if( format_specifier == VA_UINT )
		putui((uint32)(*varg++));
	else{}
}

