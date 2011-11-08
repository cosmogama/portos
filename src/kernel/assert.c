#include "assert.h"
#include "monitor.h"

void assert( BOOL b ){
	if( b ) puts( "" );
	else puts( "F" );
}
