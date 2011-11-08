#ifndef _KMALLOC_DATA_H
#define _KMALLOC_DATA_H

#include "mem_list.h"

//************************************************
// TYPES
//************************************************

//************************************************
// FUNCTIONS
//************************************************
void init_main_mem( unsigned long mbd_addr );
mem_list * get_free_ram_list(void);
mem_list * get_allocated_ram_list(void);
mem_list * get_unused_ram_list(void);

#endif
