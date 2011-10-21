#include "types.h"
#include "stream.h"

#define SECTOR_SIZE 512 		// bytes
#define NUM_SECTORS 3
#define MAX_PATH_SIZE 256

// *********************************
//	TYPES
// *********************************

typedef struct metadata{
	uint32 size_bytes;
	char filename[ MAX_PATH_SIZE ];
	BYTE permissions;
	uint64 creation_time;
} __attribute__((packed)) METADATA;

typedef struct sector{	
	BYTE data[ SECTOR_SIZE ];
} __attribute__((packed)) SECTOR;

typedef struct file{
	METADATA meta;
	SECTOR * next_file;
} __attribute__((packed)) FILE;

typedef struct dir{
	METADATA meta;
	struct dir * next_dir;
	FILE * next_file;
} __attribute__((packed)) DIR;

// *********************************
//	GLOBAL VARIABLES
// *********************************

// STREAM ostream;
SECTOR sector_map[ NUM_SECTORS ];   // map of hdd
DIR root;

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

	mount_root();

}
