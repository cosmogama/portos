#ifndef _MEM_LIST_H
#define _MEM_LIST_H

#include "types.h"

//************************************************
// TYPES
//************************************************
typedef uint32 addr;
typedef struct mem_node mem_node;

struct mem_node{
	mem_node * next;
	addr start;
	addr end;
};

typedef struct mem_list{
	mem_node * head;
	uint32 size;
} mem_list;

//************************************************
// PROTOTYPES
//************************************************
mem_node * mem_list_pop( mem_list * l );
void mem_list_push( mem_node * node , mem_list * l );
uint32 mem_list_size( mem_list * l );
void mem_list_init( mem_list * l );
void dump_mem_node( mem_node * node );

#endif
