#ifndef _RAM_LIST_H
#define _RAM_LIST_H

#include "types.h"

//************************************************
// TYPES
//************************************************
typedef uint32 addr;
typedef struct ram_node ram_node;

struct ram_node{
	ram_node * next;
	addr start;
	addr end;
};

typedef struct ram_list{
	ram_node * head;
	uint32 size;
} ram_list;

//************************************************
// PROTOTYPES
//************************************************
ram_node * ram_list_pop( ram_list * l );
void ram_list_push( ram_node * node , ram_list * l );
uint32 ram_list_size( ram_list * l );
void ram_list_init( ram_list * l );
void dump_ram_node( ram_node * node );

#endif
