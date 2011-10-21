#ifndef _MALLOC_H
#define _MALLOC_H

#include "types.h"
#include "RAM_list.h"

//************************************************
// PROTOTYPES
//************************************************
void * kmalloc( uint32 bytes_reqd , ram_list * allocated_list , ram_list * free_list , ram_list * unused_list );
void kfree( void * ptr , ram_list * allocated_list , ram_list * free_list , ram_list * unused_list );

#endif
