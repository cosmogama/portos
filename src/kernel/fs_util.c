#include "message_printer.h"
#include "fs.h"
#include "fs_util.h"
#include "mem_util.h"
#include "fs_data.h"
#include "types.h"
#include "kmalloc.h"

// *********************************
// DEFINES / CONSTANTS
// *********************************
// #define ALLOCATED_CHUNKS_DIVISIBLE_BY 4
#define DEBUG 1

// *********************************
//	GLOBALS
// *********************************

// *********************************
//	FUNCTIONS
// *********************************

uint32 kfopen(const char * filepath){
	mem_list * allocated_list = get_allocated_fs_list();
	mem_list * free_list = get_free_fs_list();
	mem_list * unused_list = get_unused_fs_list();
	uint32 desc = -1;
	int ret_val = kfopen_internal(filepath , &desc , allocated_list , free_list , unused_list);
	if( ret_val != 0 ){
		error_msg("kfopen failed");
	}
	return desc;
}

int kfopen_internal(const char * filepath , uint32 * desc , mem_list * allocated_list, mem_list * free_list , mem_list * unused_list){

	// assign descriptor
	uint32 did = new_descriptor_id();	
	DESCRIPTOR * d = kmalloc(sizeof(DESCRIPTOR));
 	d->id = did;
	d->path = filepath;
	d->sector = get_sector(filepath);

	// check if file already exists
	BOOL exists = file_exists();

	exists = !exists; // temporary delete
	allocated_list = NULL;
	free_list = NULL;
	unused_list = NULL;
	
	*desc = did;

	//if( !exists )
	// 	insert_allocated_mem_node( node , allocated_list );

	return 0;
}

BOOL file_exists(void){
	return TRUE;
}

SECTOR * get_sector( const char * path ){
	path = NULL;
	return NULL;
}

/*
void kfclose( DESCRIPTOR desc ){
	fd_node = remove_fd_node( DESCRIPTOR );
}

void kfwrite( DESCRIPTOR desc , BYTE * data , uint32 num_bytes );
	mem_list * allocated_list = get_allocated_fs_list();
	mem_list * free_list = get_free_fs_list();

	ret_val = kfwrite_internal( desc , data , num_bytes , allocated_list, free_list );
}

uint32 kfread(DESCRIPTOR desc , BYTE * buffer , uint32 size_buffer ){
	mem_list * allocated_list = get_allocated_fs_list();
	mem_list * free_list = get_free_fs_list();

	ret_val = kfread_internal( desc , buffer , size_buffer , allocated_list, free_list );
}

void kfdel(const char * filename){
}
*/

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
/*
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

*/
