#ifndef _KMALLOC_H
#define _KMALLOC_H

#include "types.h"
#include "MEM_list.h"

//************************************************
// PROTOTYPES
//************************************************
void * kmalloc( uint32 bytes_reqd );
void kfree( void * ptr );

int kmalloc_internal( uint32 bytes_reqd , void ** requested_space , mem_list * allocated_list , mem_list * free_list , mem_list * unused_list );
int kfree_internal( void * ptr , mem_list * allocated_list , mem_list * free_list , mem_list * unused_list );

#endif
