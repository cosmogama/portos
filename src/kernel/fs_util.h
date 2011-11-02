#ifndef _FS_UTIL_H
#define _FS_UTIL_H

#include "types.h"
#include "MEM_list.h"

//************************************************
// TYPES
//************************************************

typedef uint32 SECTOR;

typedef struct DESCRIPTOR{
	uint32 id;
	const char * path;
	SECTOR * sector;
} DESCRIPTOR;

//************************************************
// PROTOTYPES
//************************************************
uint32 kfopen(const char * filepath);
int kfopen_internal(const char * filepath , uint32 * desc , mem_list * allocated_list, mem_list * free_list , mem_list * unused_list);

BOOL file_exists();
SECTOR * get_sector( const char * path );

//void * kfwrite( BYTE * data , uint32 num_bytes );
//void kfread();
//void kfdel();

#endif
