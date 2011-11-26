#include "message_printer.h"
#include "IDE.h"
#include "kmalloc.h"

void t_IDE_1_1_1(void){

	

}

void t_IDE_1_4_1(void){

	// drive number
  uint8 drive_num = 0;

	// number of sectors to write
  uint8 num_sects = 1;

	// destination address on disk
  uint32 dest_addr = 0x2000; 

	// data to write to disk - initialize data in RAM
	int * x = kmalloc(4);
  *x = 21345;

	// setup segment register to zero
  // asm("mov esx , 0")
	uint16 selector = 0;

	// set offset from segment to be the RAM address holding the value to write to disk
	uint32 offset = (uint32) &x;

	// write data to disk
	ide_write_sectors( drive_num , num_sects , dest_addr , selector , offset );

	// read data from disk
  
	// free
	kfree(x);
}

void t_IDE(void){
  t_IDE_1_1_1();
  t_IDE_1_4_1();
}
