#include "kmalloc.h"
#include "mem_util.h"
#include "assert.h"
#include "printf.h"
#include "mem_list.h"
#include "monitor.h"

//********************************************************
// INTERNAL FUNCTION TESTING
//********************************************************
void t_kmalloc_kfree_1_1_1(void){
	puts("|1.1.*|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 99;
	n2.start = 104;	// n2 is the new node (not in free list yet)
	n2.end = 199;	// n2 is the new node (not in free list yet)
	n3.start = 204;
	n3.end = 299;

	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_mem_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( !combined );
	assert( n1.next == &n2 && n2.next == &n3 );
	assert( n1.start == 0 && n1.end == 99 && n2.start == 104 && n2.end == 199 && n3.start == 204 && n3.end == 299 );
	assert(unused_list.size == 10);
	assert(free_list.size == 3);
	assert(free_list.head == &n1);
	assert(unused_list.head==&raw_mem_nodes[0]);
}

void t_kmalloc_kfree_1_1_2(void){
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 99;
	n2.start = 100;	// n2 is the new node (not in free list yet)
	n2.end = 199;	// n2 is the new node (not in free list yet)
	n3.start = 204;
	n3.end = 299;

	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_mem_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( combined );
	assert( n1.next == &n3 );
	assert( n1.start == 0 && n1.end == 199 && n3.start == 204 && n3.end == 299);
	assert(unused_list.size == 11);
	assert(unused_list.head == &n2);
	assert(free_list.size == 2); // absorb new node
	assert(free_list.head == &n1);
	assert(n2.next==&raw_mem_nodes[0]);
}

void t_kmalloc_kfree_1_1_3(void){
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 99;
	n2.start = 104;	// n2 is the new node (not in free list yet)
	n2.end = 199;	// n2 is the new node (not in free list yet)
	n3.start = 200;
	n3.end = 299;

	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_mem_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( combined );
	assert( n1.next == &n2 );
	assert( n1.start == 0 && n1.end == 99 && n2.start == 104 && n2.end == 299);
	assert(unused_list.size == 11);
	assert(free_list.size == 2);
	assert(free_list.head == &n1);
	assert(unused_list.head == &n3); // next got absorbed
	assert(n3.next==&raw_mem_nodes[0]);
}

void t_kmalloc_kfree_1_1_4(void){
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3 , n4;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n4 , &free_list );
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n1 , &free_list );
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
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_mem_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( combined );
	assert( n1.next == &n4 );
	assert( n1.start == 0 && n1.end == 299 && n4.start == 450 && n4.end == 550);
	assert(unused_list.size == 12);
	assert(free_list.size == 2);
	assert(free_list.head == &n1);
	assert(unused_list.head == &n3); // next got absorbed
	assert(n3.next==&n2 && n2.next==&raw_mem_nodes[0]);
}

void t_kmalloc_kfree_1_1_5(void){
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 99;
	n2.start = 100;	// n2 is the new node (not in free list yet)
	n2.end = 199;	// n2 is the new node (not in free list yet)
	n3.start = 200;
	n3.end = 299;

	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_mem_nodes_if_possible( &n1 , &n2 , &n3 , &free_list , &unused_list );
	assert( combined );
	assert( n1.next == NULL );
	assert( n1.start == 0 && n1.end == 299 );
	assert(unused_list.size == 12);
	assert(free_list.size == 1);
	assert(free_list.head == &n1);
	assert(unused_list.head==&n3);
	assert(n3.next==&n2 && n2.next==&raw_mem_nodes[0]);
}

void t_kmalloc_kfree_1_1_6(void){
	puts("|");

	// data structures	
	mem_node n1 , n2;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n1 , &free_list );
	n2.next = NULL;
	n1.start = 0;
	n1.end = 99;
	n2.start = 100;	// n2 is the new node (not in free list yet)
	n2.end = 199;	// n2 is the new node (not in free list yet)

	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_mem_nodes_if_possible( &n1 , &n2 , NULL , &free_list , &unused_list );
	assert( combined );
	assert( n1.next == NULL );
	assert( n1.start == 0 && n1.end == 199 );
	assert(unused_list.size == 11);
	assert(free_list.size == 1);
	assert(free_list.head == &n1);
	assert(unused_list.head==&n2);
	assert(n2.next==&raw_mem_nodes[0]);
}

void t_kmalloc_kfree_1_1_7(void){
	puts("|");

	// data structures	
	mem_node n2 , n3;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	n3.next = NULL;
	n2.start = 0; // n2 is the new node (not in free list yet)
	n2.end = 99; // n2 is the new node (not in free list yet)
	n3.start = 100;	
	n3.end = 199;	

	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_mem_nodes_if_possible( NULL , &n2 , &n3 , &free_list , &unused_list );
	assert( combined );
	assert( n2.next == NULL );
	assert( n2.start == 0 && n2.end == 199 );
	assert(unused_list.size == 11);
	assert(free_list.size == 1);
	assert(free_list.head == &n2);
	assert(unused_list.head==&n3);
	assert(n3.next==&raw_mem_nodes[0]);
}

void t_kmalloc_kfree_1_1_8(void){
	puts("|");

	// data structures	
	mem_node n1 , n2;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];

	// setup free list
	mem_list_init(&free_list);
	n2.next = NULL;
	n2.start = 100;	// n2 is the new node (not in free list yet)
	n2.end = 199;	// n2 is the new node (not in free list yet)

	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// combine
	BOOL combined = combine_free_mem_nodes_if_possible( NULL , &n2 , NULL , &free_list , &unused_list );
	assert( !combined );
	assert( n2.next == NULL );
	assert( n2.start == 100 && n1.end == 199 );
	assert(unused_list.size == 10);
	assert(free_list.size == 1);
	assert(free_list.head == &n2);
	assert(unused_list.head==&raw_mem_nodes[0]);
}

void t_kmalloc_kfree_1_2_1(void){	
	puts("|1.2.*|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];

	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 2007;
	n3.start = 2008;
	n3.end = 2012;

	mem_node * free_node = find_most_suitable_free_mem_node( 2000 , &free_list , &unused_list );
	//dump_mem_node( free_node );
	assert( free_node == &n1 );
	assert(free_node->end - free_node->start + 1==2000);
	assert(free_list.size==2);
	assert(unused_list.size==10);
	assert(free_list.head == &n2);
	assert(n2.next == &n3);
}

void t_kmalloc_kfree_1_2_2(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];

	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 2007;
	n3.start = 2008;
	n3.end = 10007;

	mem_node * free_node = find_most_suitable_free_mem_node( 8000 , &free_list , &unused_list );
	//dump_mem_node( free_node );
	assert( free_node == &n3 );
	assert(free_node->end - free_node->start + 1==8000);
	assert(free_list.size==2);
	assert(unused_list.size==10);
	assert(free_list.head == &n1 && n1.next == &n2 && n2.next == NULL );
}

void t_kmalloc_kfree_1_2_3(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 2007;
	n3.start = 2008;
	n3.end = 10007;

	mem_node * free_node = find_most_suitable_free_mem_node( 500 , &free_list , &unused_list );
	mem_node * split_node = free_list.head;
	assert( free_node == &n1 );
	assert(free_node->end - free_node->start + 1==500);
	assert(split_node->end - split_node->start + 1==1500);
	assert(free_list.size==3);
	assert(unused_list.size==9);
	assert(free_list.head == &raw_mem_nodes[0]);
	assert(raw_mem_nodes[0].next == &n2 && n2.next == &n3);
	assert(unused_list.head==&raw_mem_nodes[1]);
}

void t_kmalloc_kfree_1_2_4(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 2007;
	n3.start = 2008;
	n3.end = 10007;

	mem_node * free_node = find_most_suitable_free_mem_node( 100000 , &free_list , &unused_list );
	//dump_mem_node( free_node );
	assert( free_node == NULL );
	assert(free_list.size==3);
	assert(unused_list.size==10);
	assert(free_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &n3 && n3.next == NULL);
	assert(unused_list.head==&raw_mem_nodes[0]);
}

void t_kmalloc_kfree_1_2_5(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 4999;
	n3.start = 5000;
	n3.end = 9999;

	mem_node * free_node = find_most_suitable_free_mem_node( 2500 , &free_list , &unused_list );
	mem_node * split_node = n1.next;
	assert( free_node == &n2 );
	assert(free_node->end - free_node->start + 1==2500);
	assert(split_node->end - split_node->start + 1==500);
	assert(split_node == &raw_mem_nodes[0]);
	assert(free_list.size==3);
	assert(unused_list.size==9);
	assert(free_list.head == &n1);
	assert(n1.next == &raw_mem_nodes[0] && raw_mem_nodes[0].next == &n3);
	assert(unused_list.head==&raw_mem_nodes[1]);
}

void t_kmalloc_kfree_1_2_6(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 0;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 4999;
	n3.start = 5000;
	n3.end = 9999;

	mem_node * free_node = find_most_suitable_free_mem_node( 4500 , &free_list , &unused_list );
	mem_node * split_node = n2.next;
	assert( free_node == &n3 );
	assert(free_node->end - free_node->start + 1==4500);
	assert(split_node->end - split_node->start + 1==500);
	assert(split_node == &raw_mem_nodes[0]);
	assert(free_list.size==3);
	assert(unused_list.size==9);
	assert(free_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &raw_mem_nodes[0] && raw_mem_nodes[0].next == NULL);
	assert(unused_list.head==&raw_mem_nodes[1]);
}

void t_kmalloc_kfree_1_3_1(void){	
	puts("|1.3.*|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list free_list;

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 4999;
	n3.start = 5000;
	n3.end = 9999;

	mem_node * predecessor_node = find_node_predecessor( 0 , &free_list );
	assert( predecessor_node == NULL );
	assert(free_list.size==3);
	assert(free_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &n3 && n3.next == NULL);
}

void t_kmalloc_kfree_1_3_2(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list free_list;

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 4999;
	n3.start = 5000;
	n3.end = 9999;

	mem_node * predecessor_node = find_node_predecessor( 105 , &free_list );
	assert( predecessor_node == &n1 );
	assert(free_list.size==3);
	assert(free_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &n3 && n3.next == NULL);
}

void t_kmalloc_kfree_1_3_3(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list free_list;

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 4999;
	n3.start = 5000;
	n3.end = 9999;

	mem_node * predecessor_node = find_node_predecessor( 2010 , &free_list );
	assert( predecessor_node == &n2 );
	assert(free_list.size==3);
	assert(free_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &n3 && n3.next == NULL);
}

void t_kmalloc_kfree_1_3_4(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list free_list;

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2000;
	n2.end = 4999;
	n3.start = 5000;
	n3.end = 9999;

	mem_node * predecessor_node = find_node_predecessor( 10000 , &free_list );
	assert( predecessor_node == &n3 );
	assert(free_list.size==3);
	assert(free_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &n3 && n3.next == NULL);
}

void t_kmalloc_kfree_1_4_1(void){	
	puts("|1.4.*|");

	// data structures	
	mem_node n1 , n2 , n3 , node_to_insert;
	mem_list allocated_list;

	// setup free list
	mem_list_init(&allocated_list);
	mem_list_push( &n3 , &allocated_list );
	mem_list_push( &n2 , &allocated_list );
	mem_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 50;
	node_to_insert.end = 70;
	
	insert_allocated_mem_node( &node_to_insert , &allocated_list );
	assert(allocated_list.size==4);
	assert(allocated_list.head == &node_to_insert);
	assert(node_to_insert.next == &n1 && n1.next == &n2 && n2.next == &n3 && n3.next == NULL);
}

void t_kmalloc_kfree_1_4_2(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3 , node_to_insert;
	mem_list allocated_list;

	// setup free list
	mem_list_init(&allocated_list);
	mem_list_push( &n3 , &allocated_list );
	mem_list_push( &n2 , &allocated_list );
	mem_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 2000;
	node_to_insert.end = 2050;
	
	insert_allocated_mem_node( &node_to_insert , &allocated_list );
	assert(allocated_list.size==4);
	assert(allocated_list.head == &n1);
	assert(n1.next == &node_to_insert && node_to_insert.next == &n2 && n2.next == &n3 && n3.next == NULL);
}

void t_kmalloc_kfree_1_4_3(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3 , node_to_insert;
	mem_list allocated_list;

	// setup free list
	mem_list_init(&allocated_list);
	mem_list_push( &n3 , &allocated_list );
	mem_list_push( &n2 , &allocated_list );
	mem_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 5000;
	node_to_insert.end = 5050;
	
	insert_allocated_mem_node( &node_to_insert , &allocated_list );
	assert(allocated_list.size==4);
	assert(allocated_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &node_to_insert && node_to_insert.next == &n3 && n3.next == NULL);
}

void t_kmalloc_kfree_1_4_4(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3 , node_to_insert;
	mem_list allocated_list;

	// setup free list
	mem_list_init(&allocated_list);
	mem_list_push( &n3 , &allocated_list );
	mem_list_push( &n2 , &allocated_list );
	mem_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 10000;
	node_to_insert.end = 10050;
	
	insert_allocated_mem_node( &node_to_insert , &allocated_list );
	assert(allocated_list.size==4);
	assert(allocated_list.head == &n1);
	assert(n1.next == &n2 && n2.next == &n3 && n3.next == &node_to_insert && node_to_insert.next == NULL);
}

void t_kmalloc_kfree_1_4_5(void){	
	puts("|");

	// data structures	
	mem_node node_to_insert;
	mem_list allocated_list;

	// setup free list
	mem_list_init(&allocated_list);
	node_to_insert.next = NULL;

	node_to_insert.start = 10000;
	node_to_insert.end = 10050;
	
	insert_allocated_mem_node( &node_to_insert , &allocated_list );
	assert(allocated_list.size==1);
	assert(allocated_list.head == &node_to_insert && node_to_insert.next == NULL);
}

void t_kmalloc_kfree_1_5_1(void){	
	puts("|1.5.*|");

	// data structures	
	mem_node n1 , n2 , n3 , node_to_insert;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 50;
	node_to_insert.end = 99;
	
	insert_free_mem_node( &node_to_insert , &free_list , &unused_list );
	assert(free_list.size==3);
	assert(unused_list.size==11);
	assert(free_list.head == &node_to_insert);
	assert(node_to_insert.next == &n2 && n2.next == &n3 && n3.next == NULL);
	assert(unused_list.head == &n1 && n1.next == &raw_mem_nodes[0]);
	assert(node_to_insert.start == 50 && node_to_insert.end == 1999);
}

void t_kmalloc_kfree_1_5_2(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3 , node_to_insert;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 2000;
	node_to_insert.end = 2099;
	
	insert_free_mem_node( &node_to_insert , &free_list , &unused_list );
	assert(free_list.size==2);
	assert(unused_list.size==12);
	assert(free_list.head == &n1);
	assert(n1.next==&n3 && n3.next == NULL);
	assert(unused_list.head == &n2 && n2.next == &node_to_insert && node_to_insert.next == &raw_mem_nodes[0]);
	assert(n1.start == 100 && n1.end == 4999);
}

void t_kmalloc_kfree_1_5_3(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3 , node_to_insert;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 5000;
	node_to_insert.end = 5050;
	
	insert_free_mem_node( &node_to_insert , &free_list , &unused_list );
	assert(free_list.size==3);
	assert(unused_list.size==11);
	assert(free_list.head == &n1 && n1.next==&n2 && n2.next == &n3 && n3.next == NULL);
	assert(unused_list.head == &node_to_insert && node_to_insert.next == &raw_mem_nodes[0]);
	assert(n2.start == 2100 && n2.end == 5050 && n3.start == 5100 && n3.end == 9999);
}

void t_kmalloc_kfree_1_5_4(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3 , node_to_insert;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 10000;
	node_to_insert.end = 10050;
	
	insert_free_mem_node( &node_to_insert , &free_list , &unused_list );
	assert(free_list.size==3);
	assert(unused_list.size==11);
	assert(free_list.head == &n1 && n1.next==&n2 && n2.next == &n3 && n3.next == NULL);
	assert(unused_list.head == &node_to_insert && node_to_insert.next == &raw_mem_nodes[0]);
	assert(n3.start == 5100 && n3.end == 10050);
}

void t_kmalloc_kfree_1_5_5(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3 , node_to_insert;
	mem_list free_list , unused_list;
	mem_node raw_mem_nodes[10];
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	mem_list_push( &n1 , &free_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;

	node_to_insert.start = 10050;
	node_to_insert.end = 11050;
	
	insert_free_mem_node( &node_to_insert , &free_list , &unused_list );
	assert(free_list.size==4);
	assert(unused_list.size==10);
	assert(free_list.head == &n1 && n1.next==&n2 && n2.next == &n3 && n3.next == &node_to_insert && node_to_insert.next == NULL);
	assert(unused_list.head == &raw_mem_nodes[0]);
	assert(n3.start == 5100 && n3.end == 9999 && node_to_insert.start == 10050 && node_to_insert.end == 11050);
}

void t_kmalloc_kfree_1_6_1(void){	
	puts("|1.6.*|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_node * node_removed;
	mem_list allocated_list;

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n3 , &allocated_list );
	mem_list_push( &n2 , &allocated_list );
	mem_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;
	
	void * space_to_free = (void *)100;

	node_removed = remove_allocated_mem_node( space_to_free , &allocated_list );
	assert(allocated_list.size==2);
	assert(allocated_list.head == &n2 && n2.next==&n3 && n3.next == NULL);
	assert(node_removed->start==100 && node_removed->end==1999);
}

void t_kmalloc_kfree_1_6_2(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_node * node_removed;
	mem_list allocated_list;

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n3 , &allocated_list );
	mem_list_push( &n2 , &allocated_list );
	mem_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;
	
	void * space_to_free = (void *)2100;

	node_removed = remove_allocated_mem_node( space_to_free , &allocated_list );
	assert(allocated_list.size==2);
	assert(allocated_list.head == &n1 && n1.next==&n3 && n3.next == NULL);
	assert(node_removed->start==2100 && node_removed->end==4999);
}

void t_kmalloc_kfree_1_6_3(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_node * node_removed;
	mem_list allocated_list;

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n3 , &allocated_list );
	mem_list_push( &n2 , &allocated_list );
	mem_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;
	
	void * space_to_free = (void *)5100;

	node_removed = remove_allocated_mem_node( space_to_free , &allocated_list );
	assert(allocated_list.size==2);
	assert(allocated_list.head == &n1 && n1.next==&n2 && n2.next == NULL);
	assert(node_removed->start==5100 && node_removed->end==9999);
}

void t_kmalloc_kfree_1_6_4(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_node * node_removed;
	mem_list allocated_list;

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n3 , &allocated_list );
	mem_list_push( &n2 , &allocated_list );
	mem_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;
	
	void * space_to_free = (void *)100100;

	node_removed = remove_allocated_mem_node( space_to_free , &allocated_list );
	assert(allocated_list.size==3);
	assert(allocated_list.head == &n1 && n1.next==&n2 && n2.next==&n3 && n3.next == NULL);
	assert(node_removed==NULL);
}

void t_kmalloc_kfree_1_6_5(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_node * node_removed;
	mem_list allocated_list;

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n3 , &allocated_list );
	mem_list_push( &n2 , &allocated_list );
	mem_list_push( &n1 , &allocated_list );
	n3.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n2.start = 2100;
	n2.end = 4999;
	n3.start = 5100;
	n3.end = 9999;
	
	void * space_to_free = (void *)NULL;

	node_removed = remove_allocated_mem_node( space_to_free , &allocated_list );
	assert(allocated_list.size==3);
	assert(allocated_list.head == &n1 && n1.next==&n2 && n2.next==&n3 && n3.next == NULL);
	assert(node_removed==NULL);
}

void t_kmalloc_kfree_1_6_6(void){	
	puts("|");

	// data structures	
	mem_node * node_removed;
	mem_list allocated_list;

	// setup allocated list
	mem_list_init(&allocated_list);

	void * space_to_free = (void *)100;

	node_removed = remove_allocated_mem_node( space_to_free , &allocated_list );
	assert(allocated_list.size==0);
	assert(allocated_list.head == NULL);
	assert(node_removed==NULL);
}

void t_kmalloc_kfree_1_6_7(void){	
	puts("|");

	// data structures	
	mem_node n1;
	mem_node * node_removed;
	mem_list allocated_list;

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n1 , &allocated_list );
	n1.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	
	void * space_to_free = (void *)100;

	node_removed = remove_allocated_mem_node( space_to_free , &allocated_list );
	assert(allocated_list.size==0);
	assert(allocated_list.head == NULL);
	assert(node_removed->start == 100 && node_removed->end == 1999);
}

void t_kmalloc_kfree_1_7_1(void){	
	puts("|1.7.*|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list allocated_list, free_list, unused_list;
	mem_node raw_mem_nodes[10];

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n1 , &allocated_list );
	n1.next = NULL;
	n1.start = 100;
	n1.end = 1999;

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	n3.next = NULL;
	n2.start = 40000;
	n2.end = 49999;
	n3.start = 60000;
	n3.end = 89999;
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	void * requested_space = NULL;

	int ret_val = kmalloc_internal(10000, &requested_space, &allocated_list, &free_list, &unused_list);
	assert(ret_val==0);
	assert(allocated_list.size==2);
	assert(allocated_list.head == &n1 && n1.next == &n2 && n2.next == NULL);
	assert(free_list.size==1);
	assert(free_list.head == &n3 && n3.next ==  NULL);
	assert(unused_list.size==10);
	assert(unused_list.head == &raw_mem_nodes[0]);
	assert((uint32)requested_space == 40000);
}

void t_kmalloc_kfree_1_7_2(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list allocated_list, free_list, unused_list;
	mem_node raw_mem_nodes[10];

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n1 , &allocated_list );
	n1.next = NULL;
	n1.start = 100;
	n1.end = 1999;

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	n3.next = NULL;
	n2.start = 40000;
	n2.end = 49999;
	n3.start = 60000;
	n3.end = 89999;
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	void * requested_space = NULL;

	int ret_val = kmalloc_internal(20000, &requested_space, &allocated_list, &free_list, &unused_list);
	assert(ret_val==0);
	assert(allocated_list.size==2);
	assert(allocated_list.head == &n1 && n1.next == &n3 && n3.next == NULL);
	assert(free_list.size==2);
	assert(free_list.head == &n2 && n2.next == &raw_mem_nodes[0] && raw_mem_nodes[0].next == NULL);
	assert(raw_mem_nodes[0].start==80000 && raw_mem_nodes[0].end==89999);
	assert(unused_list.size==9);
	assert(unused_list.head == &raw_mem_nodes[1]);
	assert((uint32)requested_space == 60000);
}

void t_kmalloc_kfree_1_7_3(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list allocated_list, free_list, unused_list;
	mem_node raw_mem_nodes[10];

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n1 , &allocated_list );
	n1.next = NULL;
	n1.start = 100;
	n1.end = 1999;

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	n3.next = NULL;
	n2.start = 40000;
	n2.end = 49999;
	n3.start = 60000;
	n3.end = 89999;
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	void * requested_space = NULL;

	int ret_val = kmalloc_internal(50000, &requested_space, &allocated_list, &free_list, &unused_list);
	assert(ret_val==-1);
	assert(allocated_list.size==1);
	assert(allocated_list.head == &n1 && n1.next == NULL);
	assert(free_list.size==2);
	assert(free_list.head == &n2 && n2.next == &n3 && n3.next == NULL);
	assert(unused_list.size==10);
	assert(unused_list.head == &raw_mem_nodes[0]);
	assert((uint32)requested_space == NULL);
}

void t_kmalloc_kfree_1_7_4(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3;
	mem_list allocated_list, free_list, unused_list;
	mem_node raw_mem_nodes[10];

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n1 , &allocated_list );
	n1.next = NULL;
	n1.start = 100;
	n1.end = 1999;

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	n3.next = NULL;
	n2.start = 40000;
	n2.end = 49999;
	n3.start = 60000;
	n3.end = 89999;
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	void * requested_space = NULL;

	int ret_val = kmalloc_internal(0, &requested_space, &allocated_list, &free_list, &unused_list);
	assert(ret_val==1);
	assert(allocated_list.size==1);
	assert(allocated_list.head == &n1 && n1.next == NULL);
	assert(free_list.size==2);
	assert(free_list.head == &n2 && n2.next == &n3 && n3.next == NULL);
	assert(unused_list.size==10);
	assert(unused_list.head == &raw_mem_nodes[0]);
	assert((uint32)requested_space == NULL);
}

void t_kmalloc_kfree_1_8_1(void){	
	puts("|1.8.*|");

	// data structures	
	mem_node n1 , n2 , n3 , n4;
	mem_list allocated_list, free_list, unused_list;
	mem_node raw_mem_nodes[10];

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n4 , &allocated_list );
	mem_list_push( &n1 , &allocated_list );
	n4.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n4.start = 30000;
	n4.end = 39999;

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	n3.next = NULL;
	n2.start = 40000;
	n2.end = 49999;
	n3.start = 60000;
	n3.end = 89999;
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	void * space_to_free = (void *) 30000;

	int ret_val = kfree_internal(space_to_free, &allocated_list, &free_list, &unused_list);
	assert(ret_val==0);
	assert(allocated_list.size==1);
	assert(allocated_list.head == &n1 && n1.next == NULL);
	assert(free_list.size==2);
	assert(free_list.head == &n4 && n4.next == &n3 && n3.next == NULL);
	assert(n4.start==30000 && n4.end==49999);
	assert(unused_list.size==11);
	assert(unused_list.head == &n2 && n2.next == &raw_mem_nodes[0]);
}

void t_kmalloc_kfree_1_8_2(void){	
	puts("|");

	// data structures	
	mem_node n2 , n3 , n4;
	mem_list allocated_list, free_list, unused_list;
	mem_node raw_mem_nodes[10];

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n4 , &allocated_list );
	n4.next = NULL;
	n4.start = 30000;
	n4.end = 39999;

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	n3.next = NULL;
	n2.start = 40000;
	n2.end = 49999;
	n3.start = 60000;
	n3.end = 89999;
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	void * space_to_free = (void *) 30000;

	int ret_val = kfree_internal(space_to_free, &allocated_list, &free_list, &unused_list);
	assert(ret_val==0);
	assert(allocated_list.size==0);
	assert(allocated_list.head == NULL);
	assert(free_list.size==2);
	assert(free_list.head == &n4 && n4.next == &n3 && n3.next == NULL);
	assert(n4.start==30000 && n4.end==49999);
	assert(unused_list.size==11);
	assert(unused_list.head == &n2 && n2.next == &raw_mem_nodes[0]);
}

void t_kmalloc_kfree_1_8_3(void){	
	puts("|");

	// data structures	
	mem_node n1 , n4;
	mem_list allocated_list, free_list, unused_list;
	mem_node raw_mem_nodes[10];

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n4 , &allocated_list );
	mem_list_push( &n1 , &allocated_list );
	n4.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n4.start = 30000;
	n4.end = 39999;

	// setup free list
	mem_list_init(&free_list);
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	void * space_to_free = (void *) 30000;

	int ret_val = kfree_internal(space_to_free, &allocated_list, &free_list, &unused_list);
	assert(ret_val==0);
	assert(allocated_list.size==1);
	assert(allocated_list.head == &n1 && n1.next == NULL);
	assert(free_list.size==1);
	assert(free_list.head == &n4 && n4.next == NULL);
	assert(n4.start==30000 && n4.end==39999);
	assert(unused_list.size==10);
	assert(unused_list.head == &raw_mem_nodes[0]);
}

void t_kmalloc_kfree_1_8_4(void){	
	puts("|");

	// data structures	
	mem_node n4;
	mem_list allocated_list, free_list, unused_list;
	mem_node raw_mem_nodes[10];

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n4 , &allocated_list );
	n4.next = NULL;
	n4.start = 30000;
	n4.end = 39999;

	// setup free list
	mem_list_init(&free_list);
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	void * space_to_free = (void *) 30000;

	int ret_val = kfree_internal(space_to_free, &allocated_list, &free_list, &unused_list);
	assert(ret_val==0);
	assert(allocated_list.size==0);
	assert(allocated_list.head == NULL);
	assert(free_list.size==1);
	assert(free_list.head == &n4 && n4.next == NULL);
	assert(n4.start==30000 && n4.end==39999);
	assert(unused_list.size==10);
	assert(unused_list.head == &raw_mem_nodes[0]);
}

void t_kmalloc_kfree_1_8_5(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3 , n4;
	mem_list allocated_list, free_list, unused_list;
	mem_node raw_mem_nodes[10];

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n4 , &allocated_list );
	mem_list_push( &n1 , &allocated_list );
	n4.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n4.start = 30000;
	n4.end = 39999;

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	n3.next = NULL;
	n2.start = 40000;
	n2.end = 49999;
	n3.start = 60000;
	n3.end = 89999;
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	void * space_to_free = (void *) NULL;

	int ret_val = kfree_internal(space_to_free, &allocated_list, &free_list, &unused_list);
	assert(ret_val==-1);
	assert(allocated_list.size==2);
	assert(allocated_list.head == &n1 && n1.next == &n4 && n4.next == NULL);
	assert(free_list.size==2);
	assert(free_list.head == &n2 && n2.next == &n3 && n3.next == NULL);
	assert(unused_list.size==10);
	assert(space_to_free == NULL);
}

void t_kmalloc_kfree_1_8_6(void){	
	puts("|");

	// data structures	
	mem_node n1 , n2 , n3 , n4;
	mem_list allocated_list, free_list, unused_list;
	mem_node raw_mem_nodes[10];

	// setup allocated list
	mem_list_init(&allocated_list);
	mem_list_push( &n4 , &allocated_list );
	mem_list_push( &n1 , &allocated_list );
	n4.next = NULL;
	n1.start = 100;
	n1.end = 1999;
	n4.start = 30000;
	n4.end = 39999;

	// setup free list
	mem_list_init(&free_list);
	mem_list_push( &n3 , &free_list );
	mem_list_push( &n2 , &free_list );
	n3.next = NULL;
	n2.start = 40000;
	n2.end = 49999;
	n3.start = 60000;
	n3.end = 89999;
	
	// setup unused list
	mem_list_init(&unused_list);
	int i=9;
	for( ; i>=0; i-- )
		mem_list_push( &raw_mem_nodes[i] , &unused_list ); 

	void * space_to_free = (void *) 90;

	int ret_val = kfree_internal(space_to_free, &allocated_list, &free_list, &unused_list);
	assert(ret_val==-2);
	assert(allocated_list.size==2);
	assert(allocated_list.head == &n1 && n1.next == &n4 && n4.next == NULL);
	assert(free_list.size==2);
	assert(free_list.head == &n2 && n2.next == &n3 && n3.next == NULL);
	assert(unused_list.size==10);
	assert((uint32)space_to_free == 90);
}

//***********************************************************************************
//					TEST DRIVER
//***********************************************************************************
void t_kmalloc_kfree_util(void){
	puts("<kmalloc_kfree_util>");
  t_kmalloc_kfree_1_1_1();
	t_kmalloc_kfree_1_1_2();
	t_kmalloc_kfree_1_1_3();
	t_kmalloc_kfree_1_1_4();
	t_kmalloc_kfree_1_1_5();
	t_kmalloc_kfree_1_1_6();
	t_kmalloc_kfree_1_1_7();
	t_kmalloc_kfree_1_1_8();
	t_kmalloc_kfree_1_2_1();
	t_kmalloc_kfree_1_2_2();
	t_kmalloc_kfree_1_2_3();
	t_kmalloc_kfree_1_2_4();
	t_kmalloc_kfree_1_2_5();
	t_kmalloc_kfree_1_2_6();
	t_kmalloc_kfree_1_3_1();
	t_kmalloc_kfree_1_3_2();
	t_kmalloc_kfree_1_3_3();
	t_kmalloc_kfree_1_3_4();
	t_kmalloc_kfree_1_4_1();
	t_kmalloc_kfree_1_4_2();
	t_kmalloc_kfree_1_4_3();
	t_kmalloc_kfree_1_4_4();
	t_kmalloc_kfree_1_5_1();
	t_kmalloc_kfree_1_5_2();
	t_kmalloc_kfree_1_5_3();
	t_kmalloc_kfree_1_5_4();
	t_kmalloc_kfree_1_5_5();
	t_kmalloc_kfree_1_6_1();
	t_kmalloc_kfree_1_6_2();
	t_kmalloc_kfree_1_6_3();
	t_kmalloc_kfree_1_6_4();
	t_kmalloc_kfree_1_6_5();
	t_kmalloc_kfree_1_6_6();
	t_kmalloc_kfree_1_6_7();
	t_kmalloc_kfree_1_7_1();
	t_kmalloc_kfree_1_7_2();
	t_kmalloc_kfree_1_7_3();
	t_kmalloc_kfree_1_7_4();
	t_kmalloc_kfree_1_8_1();
	t_kmalloc_kfree_1_8_2();
	t_kmalloc_kfree_1_8_3();
	t_kmalloc_kfree_1_8_4();
	t_kmalloc_kfree_1_8_5();
	t_kmalloc_kfree_1_8_6();
}

