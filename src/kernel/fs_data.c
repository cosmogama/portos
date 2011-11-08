#include "message_printer.h"
#include "fs_data.h"
#include "multiboot.h"
#include "mem_util.h"

// TODO: temporary fix, we need to remove the raw_fs_nodes structure
// 		and make the unused_list grow dynamically as needed, ie by
//    calling kmalloc to grow it...also this means getting rid of
//    populate_unused_fs_list
// arbitrarily large number...hopefully we don't run out of nodes
// otherwise we will run into many problems!
#define MAX_FS_NODES 100000

// fs that has already been allocated
static mem_list allocated_list;
// fs that is free to be allocated
static mem_list free_list;
// nodes that are unused
static mem_list unused_list;
// raw data for unused list
static mem_node raw_fs_nodes[MAX_FS_NODES];

// list of open file descriptors
static mem_list fd_list;

static uint32 descriptor = 2;

mem_list * get_allocated_fs_list(void){
	return &allocated_list;
}
mem_list * get_free_fs_list(void){
	return &free_list;
}
mem_list * get_unused_fs_list(void){
	return &unused_list;
}
mem_list * get_fd_list(void){
	return &fd_list;
}
uint32 new_descriptor_id(void){
  return descriptor++;
}

//
void populate_unused_fs_list(void){
	int i = 0;
	for( ; i<MAX_FS_NODES-1; i++ ){
		raw_fs_nodes[i].next = &raw_fs_nodes[i+1];
	}
	raw_fs_nodes[MAX_FS_NODES-1].next = NULL;
	unused_list.head = &raw_fs_nodes[0];
	unused_list.size = MAX_FS_NODES;
}

/*
* function: init_fs_data
* parameters: 
* return: void
* description: 
*
*/ 
void init_fs_data( BOOL * sector_map , uint32 num_sectors , uint32 sizeof_fs_header ){
	
	uint32 amt_free_mem_available = 0;	
	uint32 i = 0;
	uint32 m = sizeof_fs_header % SECTOR_SIZE;
	uint32 d = sizeof_fs_header / SECTOR_SIZE;
	uint32 start_of_first_sector = 0;
	
	// calculate start address of first sector
	if( m != 0 ){
		start_of_first_sector = (d+1) * SECTOR_SIZE;
	}

	// initialize fs lists
	mem_list_init( &allocated_list );
	mem_list_init( &free_list );
	mem_list_init( &unused_list );
	mem_list_init( &fd_list );

	//
	populate_unused_fs_list();

	// initialize free memory block array
  for( ; i<num_sectors; i++ ){

		if( sector_map[i] == TRUE ){
			debug_msg( "sector %u is available\n" , i);
			mem_node * free_node = mem_list_pop( &unused_list );
			free_node->start = start_of_first_sector + i * SECTOR_SIZE;
			free_node->end = free_node->start + SECTOR_SIZE;
			insert_free_mem_node( free_node , &free_list , &unused_list );
			amt_free_mem_available += SECTOR_SIZE;
		}
		else{
			debug_msg( "sector %u is NOT available\n" , i);
			mem_node * free_node = mem_list_pop( &unused_list );
			free_node->start = start_of_first_sector + i * SECTOR_SIZE;
			free_node->end = free_node->start + SECTOR_SIZE;
			insert_allocated_mem_node( free_node , &allocated_list );
		}
	}

	debug_msg("num free sectors=%u amount of space available=%u\n" , free_list.size , amt_free_mem_available );
}

