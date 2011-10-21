#ifndef _MONITOR_H
#define _MONITOR_H

#include "types.h"

void clearMonitor();
void putc( const char c  );
void puts( const char * string  );
void putb( const uint8 b );
void putsh( const short sh );
void puti( const int i );
void putl( const long l );
void putf( const float f );
void putd( const double d );
void putui( const uint32 ui );
void putush( const uint16 ush );
void puth( const uint32 ui );

#endif
