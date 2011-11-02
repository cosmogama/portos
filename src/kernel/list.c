//#include "list.h"

list * create_list(){
	list * kmalloc(sizeof(list));
	l->size = 0;
	l->head = NULL;
	return list;
}

list_node * list_pop( list * l ){
	if( l->size == 0 ) return NULL;
	list_node * node = l->head;
	l->head = l->head->next;
	void * data = node->data;
	kfree(node);
	l->size--;
	return data;
}

void list_push( void * data , list * l ){
	list_node * node = kmalloc(sizeof(list_node));
	node->next = l->head;
	l->head = node;
	node->data = data;
	l->size++;
}

uint32 list_size( list * l ){
	return l->size;
}
