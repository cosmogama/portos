#include "kmalloc.h"
#include "mem_util.h"
#include "assert.h"
#include "printf.h"
#include "mem_list.h"
#include "monitor.h"

//********************************************************
// SANITY TESTING
//********************************************************

void t_kmalloc_kfree_2_1_1(void){
	puts("|2.1.*|");
	void * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( 0 );
	assert( allocated_space == NULL );
}

void t_kmalloc_kfree_2_1_2(void){
	kfree(NULL);
	assert(TRUE);
}

void t_kmalloc_kfree_2_1_3(void){
	void * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( -1 );
	assert( allocated_space == NULL );
}

void t_kmalloc_kfree_2_1_4(void){
	void * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( 0xFFFFFFFF );
	assert( allocated_space == NULL );
}

void t_kmalloc_kfree_3_1_1(void){
	puts("|3.1.*|");
	uint32 * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( 4 );
	*allocated_space = 389;
	assert( *allocated_space == 389 );
	kfree(allocated_space);
}

void t_kmalloc_kfree_3_1_2(void){
	uint32 * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( 3 );
	*allocated_space = 389;
	assert( *allocated_space == 389 );
	kfree(allocated_space);
}

void t_kmalloc_kfree_3_1_3(void){
	typedef struct space { uint32 a; uint32 b; } space;
	space * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( 5 );
	allocated_space->a = 389;
	allocated_space->b = 672;
	assert( allocated_space->a == 389 && allocated_space->b == 672 );
	kfree(allocated_space);
}

void t_kmalloc_kfree_3_1_4(void){
	typedef struct space { uint32 a; uint32 b; } space;
	space * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( 8 );
	allocated_space->a = 389;
	allocated_space->b = 672;
	assert( allocated_space->a == 389 && allocated_space->b == 672 );
	kfree(allocated_space);
}

//
void t_kmalloc_kfree_sanity(void){
	puts("<kmalloc_kfree_sanity>");
	t_kmalloc_kfree_2_1_1();
	t_kmalloc_kfree_2_1_2();
	t_kmalloc_kfree_2_1_3();
	t_kmalloc_kfree_2_1_4();
	t_kmalloc_kfree_3_1_1();
	t_kmalloc_kfree_3_1_2();
	t_kmalloc_kfree_3_1_3();
	t_kmalloc_kfree_3_1_4();
}
