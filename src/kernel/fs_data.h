#ifndef _FS_DATA_H
#define _FS_DATA_H

#include "mem_list.h"

#define NUM_SECTORS 3
#define SECTOR_SIZE 512

//************************************************
// TYPES
//************************************************

//************************************************
// FUNCTIONS
//************************************************
void init_fs_data( BOOL * sector_map , uint32 num_sectors , uint32 sizeof_fs_header );
mem_list * get_allocated_fs_list(void);
mem_list * get_free_fs_list(void);
mem_list * get_unused_fs_list(void);
mem_list * get_fd_list(void);
uint32 new_descriptor_id(void);

#endif

