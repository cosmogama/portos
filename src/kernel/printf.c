#include "printf.h"
#include "monitor.h"

//***************************************************************
// PROTOTYPES
//***************************************************************
void print_arg( char format_specifier , va_data_t arg );

//***************************************************************
// FUNCTIONS
//***************************************************************
int printf( const char * format , va_data_t * args ){
	
	if( args == NULL ) { puts( format ); return 0; }

	int c = 0;
	int next_arg = 0;
	while( format[c] != '\0' ){
		switch( format[c] ){
			case '%': print_arg( format[++c] , args[next_arg++] ); break;
			default: putc( format[c] ); break;
		}
		c++;
	}

	return 0;
}

int printfu( const char * format , uint32 u1 ){
	va_data_t print_args[1];
	print_args[0].u = u1;
	return printf( format , print_args );
}

int printfuu( const char * format , uint32 u1 , uint32 u2 ){
	va_data_t print_args[2];
	print_args[0].u = u1;
	print_args[1].u = u2;
	return printf( format , print_args );
}

void print_arg( char format_specifier , va_data_t arg ){
	if( format_specifier == 'c' )
		putc(arg.c);
	else if( format_specifier == VA_SHORT )
		putsh(arg.sh);
	else if( format_specifier == VA_INT )
		puti(arg.i);
	else if( format_specifier == VA_LONG )
		putl(arg.l);
	else if( format_specifier == VA_FLOAT )
		putf(arg.f);
	else if( format_specifier == VA_DOUBLE )
		putd(arg.d);
	else if( format_specifier == VA_STRING )
		puts(arg.s);
	else if( format_specifier == VA_HEX )
		puth(arg.h);
	else if( format_specifier == VA_UINT )
		putui(arg.u);
	else{}
}
