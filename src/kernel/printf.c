#include "printf.h"
#include "monitor.h"
#include "types.h"
#include "message_printer.h"
#include "data.h"
#include "string.h"

//***************************************************************
// PROTOTYPES
//***************************************************************

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
	const char * format = (char *)(*varg++);

	if( format == NULL ){
		warning_msg("print format is null");
		return 0;
	}

	int c = 0;
	char format_specifier = 0;
	BOOL is_unsigned = FALSE;
	BOOL print_to_console = out == NULL;
	while( format[c] != '\0' ){
		switch( format[c] ){
			case '%':
				is_unsigned = format[++c] == 'u';
				if( is_unsigned ){
					format_specifier = format[++c];
				}else{
					format_specifier = format[c];
				}
				//puts("enter print_arg with format specifier="); putc(format_specifier); putc(' ');
				*out = print_arg( out , is_unsigned , format_specifier , varg ); 
				//puts("leave print_arg");
				varg++; 
				break;
			default: 
				if( print_to_console ) putc( format[c] );
				else{ **out = format[c]; (*out)++; }
				//puts("print a "); putc(format[c]); putc(' ');
		}
		c++;
	}

	// end 
	**out = '\0';

	return 0;
}

// returns new address for *out
char * print_arg( char ** out , BOOL is_unsigned , char format_specifier , int * varg ){

	//
	char * out_new = NULL;

	// 
	char buff[21];
	char * pbuff = &buff[0];
	BOOL print_to_console = out == NULL;
	if( print_to_console ){
		if( format_specifier == VA_STRING ){
			out_new = puts( (char *)(*varg++) );
			return out_new;
		}
		out = &pbuff;
	}

	//
	if( format_specifier == VA_BYTE )
		out_new = btoa( *out , (BYTE)(*varg++) , is_unsigned );
	else if( format_specifier == VA_CHAR ){
		(*out)[0] = (char)(*varg++);
		(*out)[1] = '\0';
		out_new = (char *) (*out + 1);
	}
	else if( format_specifier == VA_SHORT )
		out_new = shtoa( *out , (short)(*varg++) , is_unsigned );
	else if( format_specifier == VA_INT )
		out_new = itoa( *out , (int)(*varg++) , is_unsigned );
	else if( format_specifier == VA_LONG )
		out_new = ltoa( *out , (long)(*varg++) , is_unsigned );
	else if( format_specifier == VA_FLOAT )
		out_new = ftoa( *out , (float)(*varg++) );
	else if( format_specifier == VA_DOUBLE )
		out_new = dtoa( *out , (double)(*varg++) );
	else if( format_specifier == VA_INT64 )
		out_new = i64toa( *out , (int64)(*varg++) , is_unsigned );
	else if( format_specifier == VA_HEX )
		out_new = uitoh( *out , (uint32)(*varg++) );
	else if( format_specifier == VA_STRING ){
		out_new = strcpy( out , (char *)(*varg++) );
	}
	else{
		error_msg("ERROR: unrecognized format specifier=%s\n",format_specifier);
	}

	//
	if( print_to_console ) puts( *out );

	return out_new;
}

