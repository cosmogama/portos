#include "kmalloc.h"
#include "kmalloc_proto.h"
#include "kmalloc_data.h"
#include "multiboot.h"
#include "RAM_list.h"
#include "types.h"
#include "printf.h"

// *********************************
// DEFINES / CONSTANTS
// *********************************
#define ALLOCATED_CHUNKS_DIVISIBLE_BY 4
#define MIN_NUM_BYTES_TO_ALLOCATE 4
#define DEBUG 1

// *********************************
//	GLOBALS
// *********************************

// debug printing
va_data_t print_args[10];

// *********************************
//	FUNCTIONS
// *********************************

/*
*	function: malloc.
* parameters: uint32-bytes needed to allocate on the heap.
* return: void*-the pointer to the newly allocated space on the heap.
* description: The heap blocks are already implicitly allocated and ready
*   to distribute.  I have the start and end address of free memory.  I 
*   just need to give the requestor the address of the beginning of the
*   next address of free memory.
* algorithm: 
*/
void * kmalloc( uint32 bytes_reqd , ram_list * allocated_list , ram_list * free_list , ram_list * unused_list ){

	// if process is asking for zero bytes, return immediately
	if( bytes_reqd == 0 ) return NULL;

	// bytes required must be greater than or equal to this constant
	if( bytes_reqd < MIN_NUM_BYTES_TO_ALLOCATE ){
		bytes_reqd = MIN_NUM_BYTES_TO_ALLOCATE;
	}

	// byte blocks allocated must be evenly divisible by ALLOCATED_CHUNKS_DIVISIBLE_BY
	int rem = bytes_reqd % ALLOCATED_CHUNKS_DIVISIBLE_BY;
	if( rem != 0 ){
		bytes_reqd = bytes_reqd + ALLOCATED_CHUNKS_DIVISIBLE_BY - rem;
		if(DEBUG) printfu("bytes_reqd updated to=%u\n" , bytes_reqd ); 
	}
	
	// find free space
	ram_node * node = find_most_suitable_free_ram_node( bytes_reqd , unused_list , free_list );
	printfuu("found suitable RAM space %u %u\n",node->start,node->end);
	if( node == NULL ) return NULL;

	// allocate free node's space
	insert_allocated_ram_node( node , allocated_list );

	// give process address to start of newly allocated memory space
	return (void *) node->start;
}

// at the moment, a process can free another process' RAM
// bc memory is flat, no virtual translations
void kfree( void * ptr , ram_list * allocated_list , ram_list * free_list , ram_list * unused_list ){

	// can't free NULL ptr
	if( ptr == NULL ) return;

	// find allocated node to be freed
	ram_node * allocated_ram_node = remove_allocated_ram_node( ptr , allocated_list );

	// if allocated list is empty or process is trying to free RAM that isn't allocated
	// then return immediately
	if( allocated_ram_node == NULL ) return;

	// free previously allocated node
  insert_free_ram_node( allocated_ram_node , free_list , unused_list );
}

//*************************************************************************
// RAM LIST HELPER FUNCTIONS
//*************************************************************************

int some_foo(int y){
	int x = 9;
	return x * y;
}

//
ram_node * find_most_suitable_free_ram_node( uint32 bytes_reqd , ram_list * free_list , ram_list * unused_list ){
	ram_node * next_node = free_list->head;
	ram_node * prev_node = NULL;
	long diff = 0;
	//int i=0;
	//printf("[find_most_suitable_free_ram_node] dumping first few unused ram nodes",NULL);
	//for(;i<3;i++) dump_ram_node(&raw_ram_nodes[i]);

	printfu("bytes_reqd=%u\n",bytes_reqd);

	while( next_node != NULL ){

		diff = (next_node->end - next_node->start) - bytes_reqd;

		// found node with enough RAM to fill request?
		if( diff >= 0 ){

			// split node?
			if( diff != 0 ){

				// splitting...so get a new node to split to
				printfu("splitting...bytes_reqd=%u\n",bytes_reqd);
				ram_node * unused_ram_node = ram_list_pop( unused_list );
				
				// is unused list empty?
				if( unused_ram_node == NULL ){
					printf("Error: ran out of unused ram nodes!",NULL);
					return next_node;
				}

				// some_foo(12);
				printfu("after split...bytes_reqd=%u\n",bytes_reqd);

				// add new node to free list
				printfuu("urn->next=%u nn->next=%u\n",(uint32)unused_ram_node->next,(uint32)next_node->next);
				printfuu("&urn->next=%u &nn->next=%u\n",(uint32)&(unused_ram_node->next),(uint32)&(next_node->next));
				printfu("&bytes_reqd=%u\n",(uint32)&(bytes_reqd));
				unused_ram_node->next = next_node->next;
				printfu("after connect unused node to next node...bytes_reqd=%u\n",bytes_reqd);
				free_list->size++;

				// connect prev node to new node
				if( prev_node != NULL )
					prev_node->next = unused_ram_node;

				printfu("after connect prev to unused...bytes_reqd=%u\n",bytes_reqd);

				// update new node's address space, new node gets leftover space from split
				// next node is the exact match for space
				unused_ram_node->start = next_node->start + bytes_reqd;
				unused_ram_node->end = next_node->end;

				printfu("after update unused addr fields..bytes_reqd=%u\n",bytes_reqd);

				// update next node's exact address space
				printfu("bytes_reqd last=%u\n",bytes_reqd);
				next_node->end = next_node->start + bytes_reqd;
			}
	
			// found exact match or a split created an exact match
			return next_node;
		}

		// didn't find node that could fill RAM request...check next node
		prev_node = next_node;
		next_node = next_node->next;
	}

	// free_list was empty (no free RAM available)
	return NULL;
}

//
ram_node * find_node_predecessor( uint32 start_addr , ram_list * l ){
	if( l->head == NULL ) return NULL;
	
	ram_node * next_node = l->head;
	ram_node * prev_node = NULL;

	// if while loop never runs, then node should be first in list
	while( start_addr > next_node->start ){
		prev_node = next_node;
		next_node = next_node->next;
	
		// breaks if node should be last node in list
		if( next_node->next == NULL ) break;

	// if while loop condition is false, then node should be inserted between prev_node and next_node
	}

	return prev_node;
}

//
void insert_allocated_ram_node( ram_node * new_node , ram_list * allocated_list ){

	// first allocated node
	if( allocated_list->head == NULL ){
		new_node->next = NULL;
		ram_list_push( new_node , allocated_list );
		return;
	}

	ram_node * prev_node = find_node_predecessor( new_node->start , allocated_list );
	ram_node * next_node = prev_node->next;

	// add new node in list
	new_node->next = next_node;		
	prev_node->next = new_node;
	allocated_list->size++;
}

//
void insert_free_ram_node( ram_node * new_node , ram_list * free_list , ram_list * unused_list ){

	// free_list empty?
	if( free_list->head == NULL ){
		new_node->next = NULL;
		ram_list_push( new_node , free_list );
		return;
	}

	ram_node * prev_node = find_node_predecessor( new_node->start , free_list );
	ram_node * next_node = prev_node->next;

	// insert new node between prev and next
	new_node->next = next_node;
	prev_node->next = new_node;

	// try combining new node with existing adjacent nodes
	BOOL combined = combine_free_ram_nodes_if_possible( prev_node , new_node , next_node , free_list , unused_list ); 

	// when combining, new_node becomes useless as its RAM gets sucked up by existing adjacent nodes
	if( !combined ){

		// put new node in the middle of prev and next nodes
		new_node->next = next_node;		
		prev_node->next = new_node;
		free_list->size++;
	}
}

//
//void insert_unused_ram_node( ram_node * node ){
//	ram_list_push( &unused_list , node );
//}

BOOL combine_free_ram_nodes_if_possible( ram_node * prev_node , ram_node * new_node , ram_node * next_node , ram_list * free_list , ram_list * unused_list ){
	BOOL combined = FALSE;
	ram_node * left_node = new_node;

	// if prev and new can be combined, new is useless
  if( prev_node->end + 4 == new_node->start ){
		// combine prev and new
		prev_node->end = new_node->end;
		// new_node is useless
		prev_node->next = next_node;
		// recycle newly unused node
		ram_list_push( new_node , unused_list );
		// check whether prev can be combined with next now
		left_node = prev_node;
		combined = TRUE;
	}
	// if left and next can be combined, next is useless
	if( left_node->end + 4 == next_node->start ){
		// combine left and next
		left_node->end = next_node->end;
		// next is useless
		left_node->next = next_node->next;
		// recycle newly unused node
		ram_list_push( next_node , unused_list );
		// removed pre-existing node
		free_list->size--;
		combined = TRUE;
	}
	return combined;
}

//
ram_node * remove_allocated_ram_node( void * ram_node_start , ram_list * allocated_list ){

	// can't free NULL
	if( ram_node_start == NULL ) return NULL;

	// allocated list is empty?
	if( allocated_list->head == NULL ) return NULL;

	ram_node * prev_node = find_node_predecessor( (uint32) ram_node_start , allocated_list );
	ram_node * next_node = prev_node->next;

	// remove ram_node
	ram_node * node_to_free = next_node;
	prev_node->next = next_node->next;
	allocated_list->size--;
	return node_to_free;
}
