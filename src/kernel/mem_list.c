#include "mem_list.h"
#include "printf.h"

void mem_list_init( mem_list * l ){
	l->size = 0;
	l->head = NULL;
}

mem_node * mem_list_pop( mem_list * l ){
	if( l->size == 0 ) return NULL;
	mem_node * node = l->head;
	l->head = l->head->next;
	// node->next = NULL;
	l->size--;
	return node;
}

void mem_list_push( mem_node * node , mem_list * l ){
	node->next = l->head;
	l->head = node;
	l->size++;
}

uint32 mem_list_size( mem_list * l ){
	return l->size;
}

void dump_mem_node( mem_node * node ){
	printf("MN={a=%u,n=%u,s=%u,e=%u}",(uint32)node,(uint32) node->next,(uint32) node->start,(uint32) node->end);
}
