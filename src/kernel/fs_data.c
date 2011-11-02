#include "message_printer.h"
#include "fs_data.h"
#include "multiboot.h"

// fs that has already been allocated
static mem_list * allocated_list = NULL;
// fs that is free to be allocated
static mem_list * free_list = NULL;
// nodes that are unused
static mem_list * unused_list = NULL;
// list of open file descriptors
static mem_list * fd_list = NULL;

static uint32 descriptor = 2;

mem_list * get_fd_list(){
	return fd_list;
}
mem_list * get_allocated_fs_list(){
	return allocated_list;
}
mem_list * get_free_fs_list(){
	return free_list;
}
mem_list * get_unused_fs_list(){
	return unused_list;
}

uint32 new_descriptor_id(){
  return descriptor++;
}

/*
* function: init_fs
* parameters: unsigned long-the address where the multiboot data header
*   is located in memory.
* return: void
* desc
ription: initializes 
*
* mbd = multiboot data
*/ 

/*

void init_fs_data( BOOL * sector_available , uint32 num_sectors ){
	
	uint32 amt_free_fs_available = 0;	

	// initialize fs lists
	mem_list_init( &allocated_list );
	mem_list_init( &free_list );
	mem_list_init( &unused_list );
	mem_list_init( &fd_list );

	// initialize free memory block array
  for( i=0; i<num_sectors; i++ ){

		if( sector_available[i] == TRUE ){
			debug_msg( "sector %u is available\n" , i);
			fs_node * node = kmalloc(sizeof(fs_node));
			node->start = i * SECTOR_SIZE;
			node->end = (i+1) * SECTOR_SIZE;
			insert_free_fs_node( node , &free_list );
			amt_free_fs_available += SECTOR_SIZE;
		}
		else{
			debug_msg( "sector %u is NOT available\n" , i);
			fs_node * node = kmalloc(sizeof(fs_node));
			node->start = i * SECTOR_SIZE;
			node->end = (i+1) * SECTOR_SIZE;
			insert_allocated_fs_node( node , &allocated_list );
		}
	}

	debug_msg("num free sectors=%u amount of space available=%u\n" , free_list.size , amt_free_fs_available );
}
*/

