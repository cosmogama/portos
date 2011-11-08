#ifndef _MONITOR_H
#define _MONITOR_H

#include "types.h"

void clearMonitor(void);

void putb( const UBYTE b );
void putc( const char c  );
char * puts( const char * string  );

#endif
