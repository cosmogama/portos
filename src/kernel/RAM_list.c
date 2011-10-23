#include "RAM_list.h"
#include "printf.h"

void ram_list_init( ram_list * l ){
	l->size = 0;
	l->head = NULL;
}

ram_node * ram_list_pop( ram_list * l ){
	if( l->size == 0 ) return NULL;
	ram_node * node = l->head;
	l->head = l->head->next;
	// node->next = NULL;
	l->size--;
	return node;
}

void ram_list_push( ram_node * node , ram_list * l ){
	node->next = l->head;
	l->head = node;
	l->size++;
}

uint32 ram_list_size( ram_list * l ){
	return l->size;
}

void dump_ram_node( ram_node * node ){
	printf("RN={a=%u,n=%u,s=%u,e=%u}",(uint32)node,(uint32) node->next,(uint32) node->start,(uint32) node->end);
}
