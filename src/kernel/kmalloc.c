#include "message_printer.h"
#include "kmalloc.h"
#include "mem_util.h"
#include "kmalloc_data.h"
#include "multiboot.h"
#include "mem_list.h"
#include "types.h"

// *********************************
// DEFINES / CONSTANTS
// *********************************
#define ALLOCATED_CHUNKS_DIVISIBLE_BY 4
#define MIN_NUM_BYTES_TO_ALLOCATE 4
#define DEBUG 1

// *********************************
//	GLOBALS
// *********************************

// *********************************
//	FUNCTIONS
// *********************************

void * kmalloc( uint32 bytes_reqd ){
	mem_list * allocated_list = get_allocated_ram_list();
	mem_list * free_list = get_free_ram_list();
	mem_list * unused_list = get_unused_ram_list();
	void * space_requested = NULL;

	int ret_val = kmalloc_internal( bytes_reqd , &space_requested , allocated_list, free_list, unused_list );
	
	if( ret_val == 1 )
		warning_msg("WARNING: kmalloc is requesting zero bytes. ");
	if( ret_val == -1 )
		error_msg("ERROR: not enough RAM to fill kmalloc request. ");

	return space_requested;
}

void kfree( void * ptr ){
	mem_list * allocated_list = get_allocated_ram_list();
	mem_list * free_list = get_free_ram_list();
	mem_list * unused_list = get_unused_ram_list();

	int ret_val = kfree_internal( ptr , allocated_list, free_list, unused_list );

	if( ret_val == -1 )
		error_msg("ERROR: trying to free NULL pointer. ");
	if( ret_val == -2 )
		error_msg("ERROR: trying to free unallocated pointer. ");
}

/*
*	function: malloc.
* parameters: bytes_reqd=size of space requested, requested_space=a pointer
*    to the requested space after allocation, allocated_list=the allocated 
*    list structure maintained by kmalloc_data, free_list=the free 
*    list structure maintained by kmalloc_data, unused_list=the unused 
*    list structure maintained by kmalloc_data
* return: 0 for success, 1 for requesting zero bytes, -1 if there is not
*    enough RAM to fill request.
* description: The heap blocks are already implicitly allocated and ready
*   to distribute.  I have the start and end address of free memory.  I 
*   just need to give the requestor the address of the beginning of the
*   next address of free memory.
* algorithm: 
*/
int kmalloc_internal( uint32 bytes_reqd , void ** requested_space , mem_list * allocated_list , mem_list * free_list , mem_list * unused_list ){

	// if process is asking for zero bytes, return immediately
	if( bytes_reqd == 0 ){
		*requested_space = NULL;
		return 1;
	}

	// bytes required must be greater than or equal to this constant
	if( bytes_reqd < MIN_NUM_BYTES_TO_ALLOCATE ){
		bytes_reqd = MIN_NUM_BYTES_TO_ALLOCATE;
	}

	// byte blocks allocated must be evenly divisible by ALLOCATED_CHUNKS_DIVISIBLE_BY
	int rem = bytes_reqd % ALLOCATED_CHUNKS_DIVISIBLE_BY;
	if( rem != 0 ){
		bytes_reqd = bytes_reqd + ALLOCATED_CHUNKS_DIVISIBLE_BY - rem;
		debug_msg("bytes_reqd updated to=%u\n" , bytes_reqd ); 
	}
	
	// find free space
	mem_node * node = find_most_suitable_free_mem_node( bytes_reqd , free_list , unused_list );
	if( node == NULL ){
		*requested_space = NULL;
		return -1;
	}
	debug_msg("found suitable RAM space %u %u\n",node->start,node->end);

	// allocate free node's space
	insert_allocated_mem_node( node , allocated_list );

	// give process address to start of newly allocated memory space
	*requested_space = (void *) node->start;

	return 0;
}

// at the moment, a process can free another process' RAM
// bc memory is flat, no virtual translations
// return values {0 for success, -1 for trying to free NULL ptr, -2 for trying to free 
//    unallocated ptr}
int kfree_internal( void * ptr , mem_list * allocated_list , mem_list * free_list , mem_list * unused_list ){

	// can't free NULL ptr
	if( ptr == NULL ) return -1;

	// find allocated node to be freed
	mem_node * allocated_mem_node = remove_allocated_mem_node( ptr , allocated_list );

	// if allocated list is empty or process is trying to free RAM that isn't allocated
	// then return immediately
	if( allocated_mem_node == NULL ) return -2;

	// free previously allocated node
  insert_free_mem_node( allocated_mem_node , free_list , unused_list );
	
	return 0;
}
