#include "assert.h"
#include "printf.h"
#include "monitor.h"

void assert( BOOL b ){
	if( b ) puts( "S" );
	else puts( "F" );
}
