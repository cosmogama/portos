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
	// data structures	
	ram_node n1 , n2 , n3;
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 99;
	n2.start = 104;	// n2 is the new node (not in free list yet)
	n2.end = 199;	// n2 is the new node (not in free list yet)
	n3.start = 204;
	n3.end = 299;

	// setup unused list
	ram_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 
	//printfuu("size unused list=%u size free list=%u\n",unused_list.size,free_list.size);

	// combine
	BOOL combined = combine_free_ram_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( !combined );
	assert( n1.next == &n2 && n2.next == &n3 );
	assert( n1.start == 0 && n1.end == 99 && n2.start == 104 && n2.end == 199 && n3.start == 204 && n3.end == 299 );
	assert(unused_list.size == 10);
	assert(free_list.size == 3);
	assert(free_list.head == &n1);
	assert(unused_list.head==&raw_ram_nodes[0]);
	//printfuu("size unused list=%u size free list=%u\n",unused_list.size,free_list.size);
	puts("|");
}

void test_malloc_free_1_1_2(){
	// data structures	
	ram_node n1 , n2 , n3;
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 99;
	n2.start = 100;	// n2 is the new node (not in free list yet)
	n2.end = 199;	// n2 is the new node (not in free list yet)
	n3.start = 204;
	n3.end = 299;

	// setup unused list
	ram_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_ram_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( combined );
	assert( n1.next == &n3 );
	assert( n1.start == 0 && n1.end == 199 && n3.start == 204 && n3.end == 299);
	assert(unused_list.size == 11);
	assert(unused_list.head == &n2);
	assert(free_list.size == 2); // absorb new node
	assert(free_list.head == &n1);
	assert(n2.next==&raw_ram_nodes[0]);
	puts("|");
}

void test_malloc_free_1_1_3(){
	// data structures	
	ram_node n1 , n2 , n3;
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 99;
	n2.start = 104;	// n2 is the new node (not in free list yet)
	n2.end = 199;	// n2 is the new node (not in free list yet)
	n3.start = 200;
	n3.end = 299;

	// setup unused list
	ram_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_ram_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( combined );
	assert( n1.next == &n2 );
	assert( n1.start == 0 && n1.end == 99 && n2.start == 104 && n2.end == 299);
	assert(unused_list.size == 11);
	assert(free_list.size == 2);
	assert(free_list.head == &n1);
	assert(unused_list.head == &n3); // next got absorbed
	assert(n3.next==&raw_ram_nodes[0]);
	puts("|");
}

void test_malloc_free_1_1_4(){
	// data structures	
	ram_node n1 , n2 , n3 , n4;
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n4 , &free_list );
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n1 , &free_list );
	n4.next = NULL;
	n1.start = 0;
	n1.end = 99;
	n2.start = 100;	// n2 is the new node (not in free list yet)
	n2.end = 199;	// n2 is the new node (not in free list yet)
	n3.start = 200;
	n3.end = 299;
	n4.start = 450;
	n4.end = 550;

	// setup unused list
	ram_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_ram_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( combined );
	assert( n1.next == &n4 );
	assert( n1.start == 0 && n1.end == 299 && n4.start == 450 && n4.end == 550);
	assert(unused_list.size == 12);
	assert(free_list.size == 2);
	assert(free_list.head == &n1);
	assert(unused_list.head == &n3); // next got absorbed
	assert(n3.next==&n2 && n2.next==&raw_ram_nodes[0]);
	puts("|");
}

void test_malloc_free_1_1_5(){
	// data structures	
	ram_node n1 , n2 , n3;
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 99;
	n2.start = 100;	// n2 is the new node (not in free list yet)
	n2.end = 199;	// n2 is the new node (not in free list yet)
	n3.start = 200;
	n3.end = 299;

	// setup unused list
	ram_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_ram_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( combined );
	assert( n1.next == NULL );
	assert( n1.start == 0 && n1.end == 299 );
	assert(unused_list.size == 12);
	assert(free_list.size == 1);
	assert(free_list.head == &n1);
	assert(unused_list.head==&n3);
	assert(n3.next==&n2 && n2.next==&raw_ram_nodes[0]);
	puts("||");
}

void test_malloc_free_1_2_1(){	
	// data structures	
	ram_node n1 , n2 , n3;
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];

	// setup unused list
	ram_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n2 , &free_list );
	ram_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 2007;
	n3.start = 2008;
	n3.end = 2012;

	ram_node * free_node = find_most_suitable_free_ram_node( 2000 , &free_list , &unused_list );
	//dump_ram_node( free_node );
	assert( free_node == &n1 );
	assert(free_node->end - free_node->start + 1==2000);
	assert(free_list.size==2);
	assert(unused_list.size==10);
	assert(free_list.head == &n2);
	assert(n2.next == &n3);
	puts("|");
}

void test_malloc_free_1_2_2(){	
	// data structures	
	ram_node n1 , n2 , n3;
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];

	// setup unused list
	ram_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n2 , &free_list );
	ram_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 2007;
	n3.start = 2008;
	n3.end = 10007;

	ram_node * free_node = find_most_suitable_free_ram_node( 8000 , &free_list , &unused_list );
	//dump_ram_node( free_node );
	assert( free_node == &n3 );
	assert(free_node->end - free_node->start + 1==8000);
	assert(free_list.size==2);
	assert(unused_list.size==10);
	assert(free_list.head == &n1 && n1.next == &n2 && n2.next == NULL );
	puts("|");
}

void test_malloc_free_1_2_3(){	
	// data structures	
	ram_node n1 , n2 , n3;
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];
	
	// setup unused list
	ram_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n2 , &free_list );
	ram_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 2007;
	n3.start = 2008;
	n3.end = 10007;

	ram_node * free_node = find_most_suitable_free_ram_node( 500 , &free_list , &unused_list );
	ram_node * split_node = free_list.head;
	assert( free_node == &n1 );
	assert(free_node->end - free_node->start + 1==500);
	assert(split_node->end - split_node->start + 1==1500);
	assert(free_list.size==3);
	assert(unused_list.size==9);
	assert(free_list.head == &raw_ram_nodes[0]);
	assert(raw_ram_nodes[0].next == &n2 && n2.next == &n3);
	assert(unused_list.head==&raw_ram_nodes[1]);
	puts("|");
}

void test_malloc_free_1_2_4(){	
	// data structures	
	ram_node n1 , n2 , n3;
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];
	
	// setup unused list
	ram_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n2 , &free_list );
	ram_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 2007;
	n3.start = 2008;
	n3.end = 10007;

	ram_node * free_node = find_most_suitable_free_ram_node( 100000 , &free_list , &unused_list );
	//dump_ram_node( free_node );
	assert( free_node == NULL );
	assert(free_list.size==3);
	assert(unused_list.size==10);
	assert(free_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &n3 && n3.next == NULL);
	assert(unused_list.head==&raw_ram_nodes[0]);
	puts("|");
}

void test_malloc_free_1_2_5(){	
	// data structures	
	ram_node n1 , n2 , n3;
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];
	
	// setup unused list
	ram_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n2 , &free_list );
	ram_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 4999;
	n3.start = 5000;
	n3.end = 9999;

	ram_node * free_node = find_most_suitable_free_ram_node( 2500 , &free_list , &unused_list );
	ram_node * split_node = n1.next;
	assert( free_node == &n2 );
	assert(free_node->end - free_node->start + 1==2500);
	assert(split_node->end - split_node->start + 1==500);
	assert(split_node == &raw_ram_nodes[0]);
	assert(free_list.size==3);
	assert(unused_list.size==9);
	assert(free_list.head == &n1);
	assert(n1.next == &raw_ram_nodes[0] && raw_ram_nodes[0].next == &n3);
	assert(unused_list.head==&raw_ram_nodes[1]);
	puts("|");
}

void test_malloc_free_1_2_6(){	
	// data structures	
	ram_node n1 , n2 , n3;
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];
	
	// setup unused list
	ram_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n2 , &free_list );
	ram_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 4999;
	n3.start = 5000;
	n3.end = 9999;

	ram_node * free_node = find_most_suitable_free_ram_node( 4500 , &free_list , &unused_list );
	ram_node * split_node = n2.next;
	assert( free_node == &n3 );
	assert(free_node->end - free_node->start + 1==4500);
	assert(split_node->end - split_node->start + 1==500);
	assert(split_node == &raw_ram_nodes[0]);
	assert(free_list.size==3);
	assert(unused_list.size==9);
	assert(free_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &raw_ram_nodes[0] && raw_ram_nodes[0].next == NULL);
	assert(unused_list.head==&raw_ram_nodes[1]);
	puts("||");
}

void test_malloc_free_1_3_1(){	
	// data structures	
	ram_node n1 , n2 , n3;
	ram_list free_list;

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n2 , &free_list );
	ram_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 4999;
	n3.start = 5000;
	n3.end = 9999;

	ram_node * predecessor_node = find_node_predecessor( 0 , &free_list );
	assert( predecessor_node == NULL );
	assert(free_list.size==3);
	assert(free_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &n3 && n3.next == NULL);
	puts("|");
}

void test_malloc_free_1_3_2(){	
	// data structures	
	ram_node n1 , n2 , n3;
	ram_list free_list;

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n2 , &free_list );
	ram_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 4999;
	n3.start = 5000;
	n3.end = 9999;

	ram_node * predecessor_node = find_node_predecessor( 105 , &free_list );
	assert( predecessor_node == &n1 );
	assert(free_list.size==3);
	assert(free_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &n3 && n3.next == NULL);
	puts("|");
}

void test_malloc_free_1_3_3(){	
	// data structures	
	ram_node n1 , n2 , n3;
	ram_list free_list;

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n2 , &free_list );
	ram_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 4999;
	n3.start = 5000;
	n3.end = 9999;

	ram_node * predecessor_node = find_node_predecessor( 2010 , &free_list );
	assert( predecessor_node == &n2 );
	assert(free_list.size==3);
	assert(free_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &n3 && n3.next == NULL);
	puts("|");
}

void test_malloc_free_1_3_4(){	
	// data structures	
	ram_node n1 , n2 , n3;
	ram_list free_list;

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	ram_list_push( &n2 , &free_list );
	ram_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 4999;
	n3.start = 5000;
	n3.end = 9999;

	ram_node * predecessor_node = find_node_predecessor( 10000 , &free_list );
	assert( predecessor_node == &n3 );
	assert(free_list.size==3);
	assert(free_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &n3 && n3.next == NULL);
	puts("||");
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
	test_malloc_free_1_2_2();
	test_malloc_free_1_2_3();
	test_malloc_free_1_2_4();
	test_malloc_free_1_2_5();
	test_malloc_free_1_2_6();
	test_malloc_free_1_3_1();
	test_malloc_free_1_3_2();
	test_malloc_free_1_3_3();
	test_malloc_free_1_3_4();
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

