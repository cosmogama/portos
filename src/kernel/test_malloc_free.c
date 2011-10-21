#include "test_malloc_free.h"
#include "kmalloc.h"
#include "kmalloc_proto.h"
#include "assert.h"
#include "printf.h"
#include "RAM_list.h"
#include "monitor.h"

//********************************************************
// INTERNAL FUNCTION TESTING
//********************************************************
void test_malloc_free_1_1_1(){
	ram_node n1 , n2 , n3 , n4;
	n1.next = &n2;
	n2.next = &n3;
	n3.next = &n4;
	n1.start = 0;
	n1.end = 96;
	n2.start = 104;
	n2.end = 196;
	n3.start = 204;
	n3.end = 296;

	// setup unused list
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];
	int i = 0;
	for( ; i<10; i++ )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	BOOL combined = combine_free_ram_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( !combined );
	assert( n1.next == &n2 && n2.next == &n3 && n3.next == &n4 );
	assert( n1.start == 0 && n1.end == 96 );
	assert( n2.start == 104 && n2.end == 196 );
	assert( n3.start == 204 && n3.end == 296 );
	puts("|");
}

void test_malloc_free_1_1_2(){
	ram_node n1 , n2 , n3 , n4;
	n1.next = &n2;
	n2.next = &n3;
	n3.next = &n4;
	n1.start = 0;
	n1.end = 96;
	n2.start = 100;
	n2.end = 196;
	n3.start = 204;
	n3.end = 296;

	// setup unused list
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];
	int i=0;
	for( ; i<10; i++ )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	BOOL combined = combine_free_ram_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( combined );
	//dump_ram_node(&n1);
	//dump_ram_node(&n2);
	//dump_ram_node(&n3);
	assert( n1.next == &n3 && n3.next == &n4 );
	assert( n1.start == 0 && n1.end == 196 );
	assert( n3.start == 204 && n3.end == 296 );
	puts("|");
}

void test_malloc_free_1_1_3(){
	ram_node n1 , n2 , n3 , n4;
	n1.next = &n2;
	n2.next = &n3;
	n3.next = &n4;
	n1.start = 0;
	n1.end = 96;
	n2.start = 104;
	n2.end = 196;
	n3.start = 200;
	n3.end = 296;

	// setup unused list
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];
	int i=0;
	for( ; i<10; i++ )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	BOOL combined = combine_free_ram_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );	
	assert( combined );
	//dump_ram_node(&n1);
	//dump_ram_node(&n2);
	//dump_ram_node(&n3);
	//dump_ram_node(&n4);
	assert( n1.next == &n2 && n2.next == &n4 );
	assert( n1.start == 0 && n1.end == 96 );
	assert( n2.start == 104 && n3.end == 296 );
	puts("|");
}

void test_malloc_free_1_1_4(){
	ram_node n1 , n2 , n3 , n4;
	n1.next = &n2;
	n2.next = &n3;
	n3.next = &n4;
	n1.start = 0;
	n1.end = 96;
	n2.start = 100;
	n2.end = 196;
	n3.start = 200;
	n3.end = 296;
	n4.start = 304;	
	n4.end = 396;

	// setup unused list
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];
	int i=0;
	for( ; i<10; i++ )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	BOOL combined = combine_free_ram_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( combined );
	//dump_ram_node(&n1);
	//dump_ram_node(&n2);
	//dump_ram_node(&n3);
	assert( n1.next == &n4 );
	assert( n1.start == 0 && n1.end == 296 );
	puts("|");
}

void test_malloc_free_1_1_5(){
	ram_node n1 , n2 , n3;
	n1.next = &n2;
	n2.next = &n3;
	n3.next = NULL;
	n1.start = 0;
	n1.end = 96;
	n2.start = 100;
	n2.end = 196;
	n3.start = 200;
	n3.end = 296;

	// setup unused list
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];
	int i=0;
	for( ; i<10; i++ )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	BOOL combined = combine_free_ram_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( combined );
	//dump_ram_node(&n1);
	//dump_ram_node(&n2);
	//dump_ram_node(&n3);
	assert( n1.next == NULL );
	assert( n1.start == 0 && n1.end == 296 );
	puts("|");
}

void test_malloc_free_1_2_1(){	

	// setup unused list
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];
	int i=0;
	for( ; i<10; i++ )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	// setup free list
	ram_node n1 , n2 , n3;
	n1.next = &n2;
	n2.next = &n3;
	n3.next = NULL;
	n1.start = 0;
	n1.end = 1996;
	n2.start = 2000;
	n2.end = 2004;
	n3.start = 2008;
	n3.end = 2012;

	ram_node * free_node = find_most_suitable_free_ram_node( 2000 , &free_list , &unused_list );
	dump_ram_node( free_node );
	assert(free_node->end - free_node->start + 4==2000);
	/*n1 = find_most_suitable_free_ram_node(5);
	assert(n1->end-n1->start==8);
	n1 = find_most_suitable_free_ram_node(7);
	assert(n1->end-n1->start==8);
	n1 = find_most_suitable_free_ram_node(8);
	assert(n1->end-n1->start==8);
	n1 = find_most_suitable_free_ram_node(1652);
	assert(n1->end-n1->start==1652);
	//n1 = find_most_suitable_free_ram_node(3303);
	//assert(n1->end-n1->start==3304);
	//n1 = find_most_suitable_free_ram_node(1000000);
	//assert(n1->end-n1->start==1000000);
	*/
	puts("|");
}

//********************************************************
// SANITY TESTING
//********************************************************
/*
void test_malloc_free_2_1_1(){
	void * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( 0 );
	assert( allocated_space == NULL );
}

void test_malloc_free_2_1_2(){
	kfree(NULL);
	assert(TRUE);
}

void test_malloc_free_2_1_3(){
	void * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( -1 );
	assert( allocated_space == NULL );
}

void test_malloc_free_2_1_4(){
	void * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( 0xFFFFFFFF );
	assert( allocated_space == NULL );
}

void test_malloc_free_3_1_1(){
	uint32 * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( 4 );
	printfu("[]2_1_1] ptr addr=%u",(uint32)allocated_space);
	*allocated_space = 389;
	assert( *allocated_space == 389 );
	kfree(allocated_space);
}
*/

//
void test_malloc_free(){

  test_malloc_free_1_1_1();
	test_malloc_free_1_1_2();
	test_malloc_free_1_1_3();
	test_malloc_free_1_1_4();
	test_malloc_free_1_1_5();
	test_malloc_free_1_2_1();
	//test_malloc_free_2_1_1();
	//test_malloc_free_1_1_6();
	//test_malloc_free_1_1_7();
	/*test_malloc_free_1_1_1();
	test_malloc_free_1_1_1();
	test_malloc_free_1_1_1();
	test_malloc_free_1_1_1();
	test_malloc_free_1_1_1();
	test_malloc_free_1_1_1();
	test_malloc_free_1_1_1();
	test_malloc_free_1_1_1();
	test_malloc_free_1_1_1();
	test_malloc_free_1_1_1();
	test_malloc_free_1_1_1();	*/
}

