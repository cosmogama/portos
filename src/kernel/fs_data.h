#ifndef _FS_DATA_H
#define _FS_DATA_H

#include "MEM_list.h"

//************************************************
// TYPES
//************************************************

//************************************************
// FUNCTIONS
//************************************************
void init_fs_data( BOOL * sector_available , uint32 num_sectors );
mem_list * get_allocated_fs_list();
mem_list * get_free_fs_list();
mem_list * get_unused_fs_list();
mem_list * get_fd_list();
uint32 new_descriptor_id();

#endif

