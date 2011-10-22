#ifndef _KMALLOC_PROTO_H
#define _KMALLOC_PROTO_H

#include "types.h"
#include "RAM_list.h"

// *********************************
// PROTOTYPES
// *********************************
void populate_unused_list();
ram_node * find_most_suitable_free_ram_node( uint32 bytes_reqd , ram_list * free_list , ram_list * unused_list );
ram_node * find_node_predecessor( uint32 start_addr , ram_list * l );
void insert_allocated_ram_node( ram_node * new_node , ram_list * allocated_list );
void insert_free_ram_node( ram_node * new_node , ram_list * free_list , ram_list * unused_list );
BOOL combine_free_ram_nodes_if_possible( ram_node * prev_node , ram_node * new_node , ram_node * next_node , ram_list * free_list , ram_list * unused_list );
ram_node * remove_allocated_ram_node( void * ram_node_start , ram_list * allocated_list );

#endif
