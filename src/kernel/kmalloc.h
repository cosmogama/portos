#ifndef _KMALLOC_H
#define _KMALLOC_H

#include "types.h"
#include "RAM_list.h"

//************************************************
// PROTOTYPES
//************************************************
void * kmalloc( uint32 bytes_reqd );
void kfree( void * ptr );

int kmalloc_internal( uint32 bytes_reqd , void ** requested_space , ram_list * allocated_list , ram_list * free_list , ram_list * unused_list );
int kfree_internal( void * ptr , ram_list * allocated_list , ram_list * free_list , ram_list * unused_list );

#endif
