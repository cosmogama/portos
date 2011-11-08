#include "types.h"
#include "stream.h"
#include "kmalloc.h"
#include "fs_data.h"

#define MAX_PATH_SIZE 255

// *********************************
//	TYPES
// *********************************

typedef struct dir_metadata{
	char dirpath[ MAX_PATH_SIZE ];
	BYTE permissions;
	uint64 creation_time;
	uint64 modified_time;
} DIR_METADATA;

typedef struct metadata{
	char path[ MAX_PATH_SIZE ];
	BYTE permissions;
	uint64 creation_time;
	uint64 modified_time;
} METADATA;

typedef struct sector{	
	BYTE data[ SECTOR_SIZE ];
	uint32 sector_num;
} SECTOR;

//
typedef struct file{
	METADATA meta;
	uint32 size_bytes;
	SECTOR * next_sector;
} file;

//
typedef struct file_node file_node;
struct file_node{
	file_node * next_node;
	file f;
};

typedef struct dir_node dir_node;

//
typedef struct dir{
	METADATA meta;
	dir_node * child_dir;
	uint32 num_dirs;
	file_node * child_file;
	uint32 num_files;
} dir;

//
struct dir_node{
	dir_node * next;
	dir d;
};

// *********************************
//	GLOBAL VARIABLES
// *********************************

// STREAM ostream;
// SECTOR sector_map[ NUM_SECTORS ];   // map of hdd
dir root;

// *********************************
//	FUNCTIONS
// *********************************

void open_master_inode(void){
	
}

void open_inode(void){
	
}

void create_inode(void){
	
}

void mount_root(void){

}

// ****************************************************************
//
// function: read_sector_map
// parameters: BOOL * sector_map (out) , uint32 * num_sectors (out)
// return: 0 if successful, non-zero otherwise
//
// ****************************************************************
int read_sector_map( BOOL * sector_map , uint32 * num_sectors ){
	sector_map = kmalloc(sizeof(BOOL)*NUM_SECTORS);
	*num_sectors = NUM_SECTORS;
	return 0;
}

void init_fs(void){

	BOOL * sector_map = NULL;
	uint32 num_sectors = 0;
	uint32 size_fs_header = 512;

	//
	read_sector_map( sector_map , &num_sectors );

	//
  init_fs_data( sector_map , num_sectors , size_fs_header );

	// mount_root();
}

