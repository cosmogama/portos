#ifndef _LIST_H
#define _LIST_H

#include "types.h"

//************************************************
// TYPES
//************************************************
typedef struct list_node list_node;
struct list_node{
  list_node * next;
  void * data;
};

typedef struct list{
	list_node * head;
	uint32 size;
} list;

//************************************************
// PROTOTYPES
//************************************************
list * create_list();
void * list_pop( list * l );
void list_push( void * data , list * l );
uint32 list_size( list * l );

#endif
