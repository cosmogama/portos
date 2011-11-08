#include "types.h"

int strcmp( char * a , char * b ){
	char * p = a;
	char * q = b;	
	while( *p != '\0' && *q != '\0' ){
		if( *p != *q ){ 
			if( *p < *q ) 
				return -1;
			return 1;
		}
		p++;
		q++;
	}
	if( *p == '\0' && *q == '\0' ) return 0;
	if( *p == '\0' ) return -1;
	return 1;
}

char * strcpy( char ** dest , char * src  ){	
	char * d = *dest;
	const char * s = src;
	const char * null = "(null)";
	if( src == NULL ) s = null;
	while( (*d++ = *s++) != '\0' )
		continue;
	return --d;
}

