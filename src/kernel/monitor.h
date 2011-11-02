#ifndef _MONITOR_H
#define _MONITOR_H

#include "types.h"

void clearMonitor();

// ***********************************************************************
//
//			CONSOLE OUTPUT PRINT FUNCTIONS
//
// ***********************************************************************

void putb( const BYTE b );
void putc( const char c  );
char * puts( const char * string  );

#endif
