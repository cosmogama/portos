#if 0

#include "types.h"
#include "stream.h"
#include "list.h"

#define SECTOR_SIZE 512 		// bytes
#define NUM_SECTORS 3
#define MAX_PATH_SIZE 256

// *********************************
//	TYPES
// *********************************

typedef struct metadata{
	char filename[ MAX_PATH_SIZE ];
	BYTE permissions;
	uint64 creation_time;
} __attribute__((packed)) METADATA;

typedef struct sector{	
	BYTE data[ SECTOR_SIZE ];
} __attribute__((packed)) SECTOR;

//
typedef struct file{
	METADATA meta;
	uint32 size_bytes;
	SECTOR * next_sector;
} __attribute__((packed)) FILE;

typedef struct file_node{
	FILE info;
	FILE_NODE * next_node;
} __attribute__((packed)) FILE_NODE;

//
typedef struct dir{
	METADATA meta;
	DIR_NODE * head_child_dir;
	FILE_NODE * head_child_file;
} __attribute__((packed)) DIR;

typedef struct dir_node{
	DIR info;
	DIR_NODE * next_node;
} __attribute__((packed)) DIR_NODE;


// *********************************
//	GLOBAL VARIABLES
// *********************************

// STREAM ostream;
// SECTOR sector_map[ NUM_SECTORS ];   // map of hdd
// DIR root;

list * free_list;
list * allocated_list;

// *********************************
//	FUNCTIONS
// *********************************

void open_master_inode(){
	
}

void open_inode(){
	
}

void create_inode(){
	
}

void mount_root(){

}

void init_fs(){

  
	// mount_root();
}

#endif
