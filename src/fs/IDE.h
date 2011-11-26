#ifndef _IDE_H
#define _IDE_H

#include "types.h"

void ide_initialize(uint32 BAR0, uint32 BAR1, uint32 BAR2, uint32 BAR3,	uint32 BAR4);
void ide_detect(uint8 bus , uint8 device , uint8 func , uint8 Class , uint8 subclass , uint8 ProgIF );

uint8 ide_read(uint8 channel, uint8 reg);
void ide_write(uint8 channel, uint8 reg, uint8 data);

void ide_read_buffer(uint8 channel, uint8 reg, uint32 buffer, uint32 quads);

uint8 ide_polling(uint8 channel, uint32 advanced_check);
uint8 ide_print_error(uint32 drive, uint8 err);

void ide_read_sectors(uint8 drive, uint8 numsects, uint32 lba, uint16 es, uint32 edi);
uint8 ide_atapi_read(uint8 drive, uint32 lba, uint8 numsects,uint16 selector, uint32 edi);

/*
 *     FUNCTION: ide_write_sectors
 *      PURPOSE: to write data to a variable amount of sectors on disk
 *   PARAMETERS:
 *        drive=drive is the drive number which can be from 0 to 3.
 *     numsects=the number of sectors to be read/written, it is a char, as reading more than 
 *              256 sector immediately may incur performance issues. If numsects is 0, the ATA 
 *               controller will know that we want 256 sectors.
 *          lba=(LBA48): Accessing a sector by its 48-bit LBA address. As we use integers in GCC, 
 *              our maximum address is 32-bit long, which allows accessing a drive with a size of up to 2TB.
 *           es=selector is the segment selector to read from, or write to.
 *          edi=edi is the offset in that segment.
 *       RETURN: none
 * SIDE EFFECTS:
 */
void ide_write_sectors(uint8 drive, uint8 numsects, uint32 lba, uint16 es, uint32 edi);

uint8 ide_ata_access(uint8 direction, uint8 drive, uint32 lba, uint8 numsects, uint16 selector, uint32 edi);

#endif

