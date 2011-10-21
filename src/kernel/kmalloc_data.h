#ifndef _KMALLOC_DATA_H
#define _KMALLOC_DATA_H

#include "RAM_list.h"

#define MAX_RAM_NODES 100000

//************************************************
// TYPES
//************************************************
// typedef * ram_node[MAX_RAM_NODES] raw_ram_nodes_t;

//************************************************
// FUNCTIONS
//************************************************
void init_main_mem( unsigned long mbd_addr );
ram_list * get_free_list();
ram_list * get_allocated_list();
ram_list * get_unused_list();
// raw_ram_nodes_t * get_raw_ram_nodes();

#endif
