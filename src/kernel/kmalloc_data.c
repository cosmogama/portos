#include "kmalloc_data.h"
#include "mem_util.h"
#include "multiboot.h"
#include "monitor.h"
#include "printf.h"
#include "message_printer.h"

#define FREE_RAM_TYPE 1
// arbitrarily large number...hopefully we don't run out of nodes
// otherwise we will run into many problems!
#define MAX_RAM_NODES 100000

/*
typedef struct temp_s{
  int s;
	int t;
}temp_s;
//
temp_s a; 
//
temp_s f;
//
temp_s u;
*/

// RAM that is free to be allocated
static mem_list free_list;
// RAM that has already been allocated
static mem_list allocated_list;
// RAM nodes that are unused (neither in free or allocated lists)
static mem_list unused_list;
// raw data for unused list
static mem_node raw_ram_nodes[MAX_RAM_NODES];

mem_list * get_allocated_ram_list(){
	return &allocated_list;
}
mem_list * get_free_ram_list(){
	return &free_list;
}
mem_list * get_unused_ram_list(){
	return &unused_list;
}

//
void populate_unused_ram_list(){
	int i = 0;
	for( ; i<MAX_RAM_NODES-1; i++ ){
		raw_ram_nodes[i].next = &raw_ram_nodes[i+1];
	}
	raw_ram_nodes[MAX_RAM_NODES-1].next = NULL;
	unused_list.head = &raw_ram_nodes[i];

/*
	puts("a_list addr=");putui((uint32)&allocated_list);putc(' ');
	puts("f_list addr=");putui((uint32)&free_list);putc(' ');
	puts("u_list addr=");putui((uint32)&unused_list);putc(' ');
	puts("rrn addr=");putui((uint32)&raw_ram_nodes[0]);putc('\n');

	puts("a addr=");putui((uint32)&a.s);putc(' ');
	puts("f addr=");putui((uint32)&f.s);putc(' ');
	puts("u addr=");putui((uint32)&u.s);putc('\n');
*/
	/*puts("size mem_list="); putui(sizeof(mem_list)); putc(' '); putui(sizeof(free_list)); putc(' ');
	puts("unused_list.head="); putui((uint32)&unused_list); putc(' '); putui((uint32)unused_list.head); putc(' ');
	puts("first raw ram node addr="); putui((uint32)&raw_ram_nodes[0]); putc(' ');
	puts("free list addr="); putui((uint32)&free_list); putc(' '); putui((uint32)&free_list.size); putc(' ');
	unused_list.head = &raw_ram_nodes[0];
	puts("unused_list.head="); putui((uint32)&unused_list); putc(' '); putui((uint32)unused_list.head); putc(' ');
	puts("first raw ram node addr="); putui((uint32)&raw_ram_nodes[0]); putc(' ');
	puts("free list addr="); putui((uint32)&free_list); putc(' '); putui((uint32)&free_list.size); putc(' ');
	*/
	
	unused_list.head = &raw_ram_nodes[0];
	unused_list.size = MAX_RAM_NODES;
}

/*
* function: init_main_mem
* parameters: unsigned long-the address where the multiboot data header
*   is located in memory.
* return: void
* description: initializes 
*
* mbd = multiboot data
*/ 
void init_main_mem( unsigned long mbd_addr ){
	
	memory_map * mmap;    
	multiboot_info * mbd = (multiboot_info *) mbd_addr;
	mmap = (memory_map *) mbd->mmap_addr;
	uint32 amt_free_mem_available = 0;	
	debug_msg( "mmap_addr = %u mmap_length = %u\n" , mbd->mmap_addr , mbd->mmap_length);
	
	// initialize ram lists
	mem_list_init( &free_list );
	mem_list_init( &allocated_list );
	mem_list_init( &unused_list );

	//puts("size free list0="); putui(free_list.size); putc(' ');

	// initialize unused ram list
	populate_unused_ram_list();

	//puts("size free list1="); putui(free_list.size); putc(' ');

	
	// initialize free memory block array
	//int times=0;
  for 
	( 	; 
			(unsigned long) mmap < mbd->mmap_addr + mbd->mmap_length ; 
			mmap = (memory_map *) ((unsigned long) mmap + mmap->size + sizeof (mmap->size)) 
	){
      
		if( mmap->length_high == 0 && mmap->length_low == 0 ) continue;

		//putui(mmap->base_addr_low); putc(' ');
		//putui(mmap->base_addr_low + mmap->length_low - 1); putc(' ');
		//putui(mmap->length_low); putc(' ');
		//putui(mmap->type); putc('\n');
		debug_msg( "base_addr = %u end_addr = %u length = %u type = %u\n" , 
			mmap->base_addr_low , mmap->base_addr_low + mmap->length_low - 1 , mmap->length_low , mmap->type );
		//times++;

		//if( times >= 4 ) break;

		if( mmap->type == FREE_RAM_TYPE ){
			debug_msg( "adding free RAM chunk\n" );
			//puts("size free list2="); putui(free_list.size); putc(' ');
			mem_node * free_node = mem_list_pop( &unused_list );
			free_node->start = mmap->base_addr_low;
			free_node->end = mmap->base_addr_low + mmap->length_low;
			insert_free_mem_node( free_node , &free_list , &unused_list );
			//puts("size free list3="); putui(free_list.size); putc(' ');
			amt_free_mem_available += mmap->length_low;
		}
	}

	//puts("size free list end="); putui(free_list.size); putc(' ');
	debug_msg("num free nodes=%u amount of RAM available=%u\n" , free_list.size , amt_free_mem_available );
	
}

//************************************************
// TYPES
//************************************************
/*typedef struct kmalloc_init_params{
	unsigned long mbd_addr;
	mem_list * free_list;
	mem_list * free_list;
	mem_list * free_list;
	mem_node (raw_ram_nodes *)[MAX_RAM_NODES];
}kmalloc_init_params;
*/
