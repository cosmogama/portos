#ifndef _KMALLOC_PROTO_H
#define _KMALLOC_PROTO_H

#include "types.h"
#include "MEM_list.h"

// *********************************
// PROTOTYPES
// *********************************
void populate_unused_list();
mem_node * find_most_suitable_free_mem_node( uint32 bytes_reqd , mem_list * free_list , mem_list * unused_list );
mem_node * find_node_predecessor( uint32 start_addr , mem_list * l );
void insert_allocated_mem_node( mem_node * new_node , mem_list * allocated_list );
void insert_free_mem_node( mem_node * new_node , mem_list * free_list , mem_list * unused_list );
BOOL combine_free_mem_nodes_if_possible( mem_node * prev_node , mem_node * new_node , mem_node * next_node , mem_list * free_list , mem_list * unused_list );
mem_node * remove_allocated_mem_node( void * mem_node_start , mem_list * allocated_list );

#endif
