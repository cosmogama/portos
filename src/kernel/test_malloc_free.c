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
	puts("|1.1.*|");

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

	// combine
	BOOL combined = combine_free_ram_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( !combined );
	assert( n1.next == &n2 && n2.next == &n3 );
	assert( n1.start == 0 && n1.end == 99 && n2.start == 104 && n2.end == 199 && n3.start == 204 && n3.end == 299 );
	assert(unused_list.size == 10);
	assert(free_list.size == 3);
	assert(free_list.head == &n1);
	assert(unused_list.head==&raw_ram_nodes[0]);
}

void test_malloc_free_1_1_2(){
	puts("|");

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
}

void test_malloc_free_1_1_3(){
	puts("|");

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
}

void test_malloc_free_1_1_4(){
	puts("|");

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
}

void test_malloc_free_1_1_5(){
	puts("|");

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
}

void test_malloc_free_1_1_6(){
	puts("|");

	// data structures	
	ram_node n1 , n2;
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n1 , &free_list );
	n2.next = NULL;
	n1.start = 0;
	n1.end = 99;
	n2.start = 100;	// n2 is the new node (not in free list yet)
	n2.end = 199;	// n2 is the new node (not in free list yet)

	// setup unused list
	ram_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_ram_nodes_if_possible( &n1 , &n2 , NULL , &free_list , &unused_list );
	assert( combined );
	assert( n1.next == NULL );
	assert( n1.start == 0 && n1.end == 199 );
	assert(unused_list.size == 11);
	assert(free_list.size == 1);
	assert(free_list.head == &n1);
	assert(unused_list.head==&n2);
	assert(n2.next==&raw_ram_nodes[0]);
}

void test_malloc_free_1_1_7(){
	puts("|");

	// data structures	
	ram_node n2 , n3;
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];

	// setup free list
	ram_list_init(&free_list);
	ram_list_push( &n3 , &free_list );
	n3.next = NULL;
	n2.start = 0; // n2 is the new node (not in free list yet)
	n2.end = 99; // n2 is the new node (not in free list yet)
	n3.start = 100;	
	n3.end = 199;	

	// setup unused list
	ram_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_ram_nodes_if_possible( NULL , &n2 , &n3 , &free_list , &unused_list );
	assert( combined );
	assert( n2.next == NULL );
	assert( n2.start == 0 && n2.end == 199 );
	assert(unused_list.size == 11);
	assert(free_list.size == 1);
	assert(free_list.head == &n2);
	assert(unused_list.head==&n3);
	assert(n3.next==&raw_ram_nodes[0]);
}

void test_malloc_free_1_1_8(){
	puts("|");

	// data structures	
	ram_node n1 , n2;
	ram_list free_list , unused_list;
	ram_node raw_ram_nodes[10];

	// setup free list
	ram_list_init(&free_list);
	n2.next = NULL;
	n2.start = 100;	// n2 is the new node (not in free list yet)
	n2.end = 199;	// n2 is the new node (not in free list yet)

	// setup unused list
	ram_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		ram_list_push( &raw_ram_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_ram_nodes_if_possible( NULL , &n2 , NULL , &free_list , &unused_list );
	assert( !combined );
	assert( n2.next == NULL );
	assert( n2.start == 100 && n1.end == 199 );
	assert(unused_list.size == 10);
	assert(free_list.size == 1);
	assert(free_list.head == &n2);
	assert(unused_list.head==&raw_ram_nodes[0]);
}

void test_malloc_free_1_2_1(){	
	puts("|1.2.*|");

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
}

void test_malloc_free_1_2_2(){	
	puts("|");

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
}

void test_malloc_free_1_2_3(){	
	puts("|");

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
}

void test_malloc_free_1_2_4(){	
	puts("|");

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
}

void test_malloc_free_1_2_5(){	
	puts("|");

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
}

void test_malloc_free_1_2_6(){	
	puts("|");

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
}

void test_malloc_free_1_3_1(){	
	puts("|1.3.*|");

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
}

void test_malloc_free_1_3_2(){	
	puts("|");

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
}

void test_malloc_free_1_3_3(){	
	puts("|");

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
}

void test_malloc_free_1_3_4(){	
	puts("|");

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
}

void test_malloc_free_1_4_1(){	
	puts("|1.4.*|");

	// data structures	
	ram_node n1 , n2 , n3 , node_to_insert;
	ram_list allocated_list;

	// setup free list
	ram_list_init(&allocated_list);
	ram_list_push( &n3 , &allocated_list );
	ram_list_push( &n2 , &allocated_list );
	ram_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 50;
	node_to_insert.end = 70;
	
	insert_allocated_ram_node( &node_to_insert , &allocated_list );
	assert(allocated_list.size==4);
	assert(allocated_list.head == &node_to_insert);
	assert(node_to_insert.next == &n1 && n1.next == &n2 && n2.next == &n3 && n3.next == NULL);
}

void test_malloc_free_1_4_2(){	
	puts("|");

	// data structures	
	ram_node n1 , n2 , n3 , node_to_insert;
	ram_list allocated_list;

	// setup free list
	ram_list_init(&allocated_list);
	ram_list_push( &n3 , &allocated_list );
	ram_list_push( &n2 , &allocated_list );
	ram_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 2000;
	node_to_insert.end = 2050;
	
	insert_allocated_ram_node( &node_to_insert , &allocated_list );
	assert(allocated_list.size==4);
	assert(allocated_list.head == &n1);
	assert(n1.next == &node_to_insert && node_to_insert.next == &n2 && n2.next == &n3 && n3.next == NULL);
}

void test_malloc_free_1_4_3(){	
	puts("|");

	// data structures	
	ram_node n1 , n2 , n3 , node_to_insert;
	ram_list allocated_list;

	// setup free list
	ram_list_init(&allocated_list);
	ram_list_push( &n3 , &allocated_list );
	ram_list_push( &n2 , &allocated_list );
	ram_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 5000;
	node_to_insert.end = 5050;
	
	insert_allocated_ram_node( &node_to_insert , &allocated_list );
	assert(allocated_list.size==4);
	assert(allocated_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &node_to_insert && node_to_insert.next == &n3 && n3.next == NULL);
}

void test_malloc_free_1_4_4(){	
	puts("|");

	// data structures	
	ram_node n1 , n2 , n3 , node_to_insert;
	ram_list allocated_list;

	// setup free list
	ram_list_init(&allocated_list);
	ram_list_push( &n3 , &allocated_list );
	ram_list_push( &n2 , &allocated_list );
	ram_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 10000;
	node_to_insert.end = 10050;
	
	insert_allocated_ram_node( &node_to_insert , &allocated_list );
	assert(allocated_list.size==4);
	assert(allocated_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &n3 && n3.next == &node_to_insert && node_to_insert.next == NULL);
}

void test_malloc_free_1_5_1(){	
	puts("|1.5.*|");

	// data structures	
	ram_node n1 , n2 , n3 , node_to_insert;
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
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 50;
	node_to_insert.end = 99;
	
	insert_free_ram_node( &node_to_insert , &free_list , &unused_list );
	assert(free_list.size==3);
	assert(unused_list.size==11);
	assert(free_list.head == &node_to_insert);
	assert(node_to_insert.next == &n2 && n2.next == &n3 && n3.next == NULL);
	assert(unused_list.head == &n1 && n1.next == &raw_ram_nodes[0]);
	assert(node_to_insert.start == 50 && node_to_insert.end == 1999);
}

void test_malloc_free_1_5_2(){	
	puts("|");

	// data structures	
	ram_node n1 , n2 , n3 , node_to_insert;
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
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 2000;
	node_to_insert.end = 2099;
	
	insert_free_ram_node( &node_to_insert , &free_list , &unused_list );
	assert(free_list.size==2);
	assert(unused_list.size==12);
	assert(free_list.head == &n1);
	assert(n1.next==&n3 && n3.next == NULL);
	assert(unused_list.head == &n2 && n2.next == &node_to_insert && node_to_insert.next == &raw_ram_nodes[0]);
	assert(n1.start == 100 && n1.end == 4999);
}

void test_malloc_free_1_5_3(){	
	puts("|");

	// data structures	
	ram_node n1 , n2 , n3 , node_to_insert;
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
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 5000;
	node_to_insert.end = 5050;
	
	insert_free_ram_node( &node_to_insert , &free_list , &unused_list );
	assert(free_list.size==3);
	assert(unused_list.size==11);
	assert(free_list.head == &n1 && n1.next==&n2 && n2.next == &n3 && n3.next == NULL);
	assert(unused_list.head == &node_to_insert && node_to_insert.next == &raw_ram_nodes[0]);
	assert(n2.start == 2100 && n2.end == 5050 && n3.start == 5100 && n3.end == 9999);
}

void test_malloc_free_1_5_4(){	
	puts("|");

	// data structures	
	ram_node n1 , n2 , n3 , node_to_insert;
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
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 10000;
	node_to_insert.end = 10050;
	
	insert_free_ram_node( &node_to_insert , &free_list , &unused_list );
	assert(free_list.size==3);
	assert(unused_list.size==11);
	assert(free_list.head == &n1 && n1.next==&n2 && n2.next == &n3 && n3.next == NULL);
	assert(unused_list.head == &node_to_insert && node_to_insert.next == &raw_ram_nodes[0]);
	assert(n3.start == 5100 && n3.end == 10050);
}

void test_malloc_free_1_5_5(){	
	puts("|");

	// data structures	
	ram_node n1 , n2 , n3 , node_to_insert;
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
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 10050;
	node_to_insert.end = 11050;
	
	insert_free_ram_node( &node_to_insert , &free_list , &unused_list );
	assert(free_list.size==4);
	assert(unused_list.size==10);
	assert(free_list.head == &n1 && n1.next==&n2 && n2.next == &n3 && n3.next == &node_to_insert && node_to_insert.next == NULL);
	assert(unused_list.head == &raw_ram_nodes[0]);
	assert(n3.start == 5100 && n3.end == 9999 && node_to_insert.start == 10050 && node_to_insert.end == 11050);
}

void test_malloc_free_1_6_1(){	
	puts("|1.6.*|");

	// data structures	
	ram_node n1 , n2 , n3;
	ram_node * node_removed;
	ram_list allocated_list;

	// setup allocated list
	ram_list_init(&allocated_list);
	ram_list_push( &n3 , &allocated_list );
	ram_list_push( &n2 , &allocated_list );
	ram_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;
	
	void * space_to_free = (void *)100;

	node_removed = remove_allocated_ram_node( space_to_free , &allocated_list );
	assert(allocated_list.size==2);
	assert(allocated_list.head == &n2 && n2.next==&n3 && n3.next == NULL);
	assert(node_removed->start==100 && node_removed->end==1999);
}

void test_malloc_free_1_6_2(){	
	puts("|");

	// data structures	
	ram_node n1 , n2 , n3;
	ram_node * node_removed;
	ram_list allocated_list;

	// setup allocated list
	ram_list_init(&allocated_list);
	ram_list_push( &n3 , &allocated_list );
	ram_list_push( &n2 , &allocated_list );
	ram_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;
	
	void * space_to_free = (void *)2100;

	node_removed = remove_allocated_ram_node( space_to_free , &allocated_list );
	assert(allocated_list.size==2);
	assert(allocated_list.head == &n1 && n1.next==&n3 && n3.next == NULL);
	assert(node_removed->start==2100 && node_removed->end==4999);
}

void test_malloc_free_1_6_3(){	
	puts("|");

	// data structures	
	ram_node n1 , n2 , n3;
	ram_node * node_removed;
	ram_list allocated_list;

	// setup allocated list
	ram_list_init(&allocated_list);
	ram_list_push( &n3 , &allocated_list );
	ram_list_push( &n2 , &allocated_list );
	ram_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;
	
	void * space_to_free = (void *)5100;

	node_removed = remove_allocated_ram_node( space_to_free , &allocated_list );
	assert(allocated_list.size==2);
	assert(allocated_list.head == &n1 && n1.next==&n2 && n2.next == NULL);
	assert(node_removed->start==5100 && node_removed->end==9999);
}

void test_malloc_free_1_6_4(){	
	puts("|");

	// data structures	
	ram_node n1 , n2 , n3;
	ram_node * node_removed;
	ram_list allocated_list;

	// setup allocated list
	ram_list_init(&allocated_list);
	ram_list_push( &n3 , &allocated_list );
	ram_list_push( &n2 , &allocated_list );
	ram_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;
	
	void * space_to_free = (void *)100100;

	node_removed = remove_allocated_ram_node( space_to_free , &allocated_list );
	assert(allocated_list.size==3);
	assert(allocated_list.head == &n1 && n1.next==&n2 && n2.next==&n3 && n3.next == NULL);
	assert(node_removed==NULL);
}

void test_malloc_free_1_6_5(){	
	puts("|");

	// data structures	
	ram_node n1 , n2 , n3;
	ram_node * node_removed;
	ram_list allocated_list;

	// setup allocated list
	ram_list_init(&allocated_list);
	ram_list_push( &n3 , &allocated_list );
	ram_list_push( &n2 , &allocated_list );
	ram_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;
	
	void * space_to_free = (void *)NULL;

	node_removed = remove_allocated_ram_node( space_to_free , &allocated_list );
	assert(allocated_list.size==3);
	assert(allocated_list.head == &n1 && n1.next==&n2 && n2.next==&n3 && n3.next == NULL);
	assert(node_removed==NULL);
}

void test_malloc_free_1_6_6(){	
	puts("|");

	// data structures	
	ram_node * node_removed;
	ram_list allocated_list;

	// setup allocated list
	ram_list_init(&allocated_list);

	void * space_to_free = (void *)100;

	node_removed = remove_allocated_ram_node( space_to_free , &allocated_list );
	assert(allocated_list.size==0);
	assert(allocated_list.head == NULL);
	assert(node_removed==NULL);
}

void test_malloc_free_1_6_7(){	
	puts("|");

	// data structures	
	ram_node n1;
	ram_node * node_removed;
	ram_list allocated_list;

	// setup allocated list
	ram_list_init(&allocated_list);
	ram_list_push( &n1 , &allocated_list );
	n1.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	
	void * space_to_free = (void *)100;

	node_removed = remove_allocated_ram_node( space_to_free , &allocated_list );
	assert(allocated_list.size==0);
	assert(allocated_list.head == NULL);
	assert(node_removed->start == 100 && node_removed->end == 1999);
}

//********************************************************
// SANITY TESTING
//********************************************************

void test_malloc_free_2_1_1(){
	puts("|2.1.*|");

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
	puts("|3.1.*|");
	uint32 * allocated_space = (void *) 0xBADCAFE;
	allocated_space = kmalloc( 4 );
	printfu("[]2_1_1] ptr addr=%u",(uint32)allocated_space);
	*allocated_space = 389;
	assert( *allocated_space == 389 );
	kfree(allocated_space);
}

//
void test_malloc_free(){
  test_malloc_free_1_1_1();
	test_malloc_free_1_1_2();
	test_malloc_free_1_1_3();
	test_malloc_free_1_1_4();
	test_malloc_free_1_1_5();
	test_malloc_free_1_1_6();
	test_malloc_free_1_1_7();
	test_malloc_free_1_1_8();
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
	test_malloc_free_1_4_1();
	test_malloc_free_1_4_2();
	test_malloc_free_1_4_3();
	test_malloc_free_1_4_4();
	test_malloc_free_1_5_1();
	test_malloc_free_1_5_2();
	test_malloc_free_1_5_3();
	test_malloc_free_1_5_4();
	test_malloc_free_1_5_5();
	test_malloc_free_1_6_1();
	test_malloc_free_1_6_2();
	test_malloc_free_1_6_3();
	test_malloc_free_1_6_4();
	test_malloc_free_1_6_5();
	test_malloc_free_1_6_6();
	test_malloc_free_1_6_7();
	/*test_malloc_free_1_4_2();
	test_malloc_free_1_4_3();
	test_malloc_free_1_4_4();
	test_malloc_free_1_5_1();
	test_malloc_free_1_5_2();
	test_malloc_free_1_5_3();
	test_malloc_free_1_5_4();
	test_malloc_free_1_6_1();
	test_malloc_free_1_6_2();
	test_malloc_free_1_6_3();
	test_malloc_free_1_6_4();*/
	//test_malloc_free_2_1_1();
	//test_malloc_free_2_1_2();
	//test_malloc_free_2_1_3();
	//test_malloc_free_2_1_4();
}

