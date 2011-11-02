#include "mem_util.h"
#include "message_printer.h"

//*************************************************************************
// MEMORY LIST HELPER FUNCTIONS
//*************************************************************************

//
mem_node * find_most_suitable_free_mem_node( uint32 bytes_reqd , mem_list * free_list , mem_list * unused_list ){
	mem_node * next_node = free_list->head;
	mem_node * prev_node = NULL;
	mem_node * next_nodes_replacement = NULL;
	long diff = 0;

	while( next_node != NULL ){

		// next node's next is next_nodes_replacement
		next_nodes_replacement = next_node->next;

		diff = (next_node->end - next_node->start + 1) - bytes_reqd;

		// found node with enough MEM to fill request?
		if( diff >= 0 ){

			// split node?
			if( diff != 0 ){

				// splitting...so get a new node to split to
				mem_node * unused_mem_node = mem_list_pop( unused_list );
				
				// is unused list empty?
				if( unused_mem_node == NULL ){
					error_msg("Error: ran out of unused mem nodes!");
					return next_node;
				}

				// add new node to free list
				unused_mem_node->next = next_node->next;
				free_list->size++;

				// update new node's address space, new node gets leftover space from split
				// next node is the exact match for space
				unused_mem_node->start = next_node->start + bytes_reqd;
				unused_mem_node->end = next_node->end;

				// update next node's exact address space
				next_node->end = next_node->start + bytes_reqd - 1;

				// unused node is next_nodes_replacement
				next_nodes_replacement = unused_mem_node;
			}
			
			// connect prev_node/free_list to next node's replacement
			if( prev_node != NULL )
				prev_node->next = next_nodes_replacement;
			else
				free_list->head = next_nodes_replacement;
	
			// found exact match or a split created an exact match
			free_list->size--;
			return next_node;
		}

		// didn't find node that could fill MEM request...check next node
		prev_node = next_node;
		next_node = next_node->next;
	}

	// free_list was empty (no free MEM available)
	return NULL;
}

//
mem_node * find_node_predecessor( uint32 start_addr , mem_list * l ){
	if( l->head == NULL ) return NULL;
	
	mem_node * next_node = l->head;
	mem_node * prev_node = NULL;

	// if while loop never runs, then node should be first in list
	while( start_addr > next_node->start ){
		prev_node = next_node;
		next_node = next_node->next;
	
		// breaks if node should be last node in list
		if( next_node == NULL ) break;

	// if while loop condition is false, then node should be inserted between prev_node and next_node
	}

	return prev_node;
}

//
void insert_allocated_mem_node( mem_node * new_node , mem_list * allocated_list ){

	// allocated list empty?
	if( allocated_list->head == NULL ){
		new_node->next = NULL;
		mem_list_push( new_node , allocated_list );
		return;
	}

	mem_node * prev_node = find_node_predecessor( new_node->start , allocated_list );
	mem_node * next_node = NULL;

	// insert mem_node
	if( prev_node != NULL ){
		next_node = prev_node->next;
		prev_node->next = new_node;
	}
	else{
		next_node = allocated_list->head;
		allocated_list->head = new_node;
	}

	new_node->next = next_node;		
	allocated_list->size++;
}

//
void insert_free_mem_node( mem_node * new_node , mem_list * free_list , mem_list * unused_list ){

	// free list empty?
	if( free_list->head == NULL ){
		new_node->next = NULL;
		mem_list_push( new_node , free_list );
		return;
	}

	mem_node * prev_node = find_node_predecessor( new_node->start , free_list );	
	mem_node * next_node = NULL;

	// add mem_node
	if( prev_node != NULL ){
		next_node = prev_node->next;
	}
	else{
		next_node = free_list->head;
	}

	// try combining new node with existing adjacent nodes
	combine_free_mem_nodes_if_possible( prev_node , new_node , next_node , free_list , unused_list ); 
}

BOOL combine_free_mem_nodes_if_possible( mem_node * prev_node , mem_node * new_node , mem_node * next_node , mem_list * free_list , mem_list * unused_list ){
	BOOL combined = FALSE;
	mem_node * left_node = new_node;

	// connect prev, new, and next to begin with
	if( prev_node != NULL ) 
		prev_node->next = new_node;
	else
		free_list->head = new_node;
	new_node->next = next_node;
	free_list->size++;

	// if prev and new can be combined, new is useless
  if( prev_node != NULL && prev_node->end + 1 == new_node->start ){
		//printf("combining prev new",NULL);
		// combine prev and new
		prev_node->end = new_node->end;
		// new_node is useless
		prev_node->next = next_node;
		// recycle newly unused node
		mem_list_push( new_node , unused_list );
		free_list->size--;
		combined = TRUE;
		// check whether prev can be combined with next now
		left_node = prev_node;
	}
	// if left and next can be combined, next is useless
	if( next_node != NULL && left_node->end + 1 == next_node->start ){
		//printf("combining left next",NULL);
		// combine left and next
		left_node->end = next_node->end;
		// next is useless
		left_node->next = next_node->next;
		// recycle newly unused node
		mem_list_push( next_node , unused_list );
		free_list->size--;
		combined = TRUE;
	}
	return combined;
}

//
mem_node * remove_allocated_mem_node( void * mem_node_start , mem_list * allocated_list ){

	// can't free NULL
	if( mem_node_start == NULL ) return NULL;

	// allocated list is empty?
	if( allocated_list->head == NULL ) return NULL;

	mem_node * prev_node = find_node_predecessor( (uint32) mem_node_start , allocated_list );
	mem_node * next_node = NULL;

	// get next_node
	if( prev_node != NULL ){
		next_node = prev_node->next;
	}
	else{
		next_node = allocated_list->head;
	}

	// check if exact match was found
	if( next_node->start != (uint32) mem_node_start ) return NULL;	

	// remove mem_node bc exact match was found
	if( prev_node != NULL ){
		prev_node->next = next_node->next;
	}
	else{
		allocated_list->head = next_node->next;
	}

	allocated_list->size--;
	return next_node;
}
