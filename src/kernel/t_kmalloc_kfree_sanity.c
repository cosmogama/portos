#include "t_kmalloc_kfree_sanity.h"
#include "kmalloc.h"
#include "kmalloc_proto.h"
#include "assert.h"
#include "printf.h"
#include "RAM_list.h"
#include "monitor.h"

//********************************************************
// SANITY TESTING
//********************************************************

void t_kmalloc_kfree_2_1_1(){
	puts("|2.1.*|");
	void * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( 0 );
	assert( allocated_space == NULL );
}

void t_kmalloc_kfree_2_1_2(){
	kfree(NULL);
	assert(TRUE);
}

void t_kmalloc_kfree_2_1_3(){
	void * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( -1 );
	assert( allocated_space == NULL );
}

void t_kmalloc_kfree_2_1_4(){
	void * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( 0xFFFFFFFF );
	assert( allocated_space == NULL );
}

void t_kmalloc_kfree_3_1_1(){
	puts("|3.1.*|");
	uint32 * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( 4 );
	printfu("[]2_1_1] ptr addr=%u",(uint32)allocated_space);
	*allocated_space = 389;
	assert( *allocated_space == 389 );
	kfree(allocated_space);
}

//
void t_kmalloc_kfree_sanity(){
	t_kmalloc_kfree_2_1_1();
	t_kmalloc_kfree_2_1_2();
	t_kmalloc_kfree_2_1_3();
	t_kmalloc_kfree_2_1_4();
}

