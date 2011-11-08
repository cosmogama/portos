#include "types.h"

int 
memcpy( void * dest , void * src , uint32 numBytes ){

	uint32 i = 0;	
	char * sptr = (char *) src;
	char * dptr = (char *) dest;
	while( i < numBytes ){
		*dptr = *sptr;
		sptr++;
		dptr++;
		i++;
	}

	return i;
}

