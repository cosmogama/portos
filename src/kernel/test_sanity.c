#include "assert.h"

void test_sanity(){
	assert(TRUE);
	assert(FALSE);
	assert( 1 == 1 );
	assert( 1 == 0 );
}
