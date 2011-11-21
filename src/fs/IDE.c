// http://wiki.osdev.org/IDE

#include "IDE.h"
#include "IO.h"
#include "printf.h"
#include "kutil.h"

#define ATA_SR_BSY     0x80
#define ATA_SR_DRDY    0x40
#define ATA_SR_DF      0x20
#define ATA_SR_DSC     0x10
#define ATA_SR_DRQ     0x08
#define ATA_SR_CORR    0x04
#define ATA_SR_IDX     0x02
#define ATA_SR_ERR     0x01

// The Command/Status Port returns a bit mask referring to the status of a channel when read.
#define ATA_ER_BBK      0x80
#define ATA_ER_UNC      0x40
#define ATA_ER_MC       0x20
#define ATA_ER_IDNF     0x10
#define ATA_ER_MCR      0x08
#define ATA_ER_ABRT     0x04
#define ATA_ER_TK0NF    0x02
#define ATA_ER_AMNF     0x01

// The Features/Error Port, which returns the most recent error upon read, has these possible bit masks
#define ATA_CMD_READ_PIO          0x20
#define ATA_CMD_READ_PIO_EXT      0x24
#define ATA_CMD_READ_DMA          0xC8
#define ATA_CMD_READ_DMA_EXT      0x25
#define ATA_CMD_WRITE_PIO         0x30
#define ATA_CMD_WRITE_PIO_EXT     0x34
#define ATA_CMD_WRITE_DMA         0xCA
#define ATA_CMD_WRITE_DMA_EXT     0x35
#define ATA_CMD_CACHE_FLUSH       0xE7
#define ATA_CMD_CACHE_FLUSH_EXT   0xEA
#define ATA_CMD_PACKET            0xA0
#define ATA_CMD_IDENTIFY_PACKET   0xA1
#define ATA_CMD_IDENTIFY          0xEC

// When you write to the Command/Status port, you are executing one of the commands above.
#define      ATAPI_CMD_READ       0xA8
#define      ATAPI_CMD_EJECT      0x1B

// ATA_CMD_IDENTIFY_PACKET and ATA_CMD_IDENTIFY return a buffer of 512 bytes called the identification space; the following definitions are used to read information from the identification space.
#define ATA_IDENT_DEVICETYPE   0
#define ATA_IDENT_CYLINDERS    2
#define ATA_IDENT_HEADS        6
#define ATA_IDENT_SECTORS      12
#define ATA_IDENT_SERIAL       20
#define ATA_IDENT_MODEL        54
#define ATA_IDENT_CAPABILITIES 98
#define ATA_IDENT_FIELDVALID   106
#define ATA_IDENT_MAX_LBA      120
#define ATA_IDENT_COMMANDSETS  164
#define ATA_IDENT_MAX_LBA_EXT  200

// When you select a drive, you should specify the interface type and whether it is the master or slave:
#define IDE_ATA        0x00
#define IDE_ATAPI      0x01 
#define ATA_MASTER     0x00
#define ATA_SLAVE      0x01

// Task File is a range of 8 ports which are offsets from BAR0 (primary channel) and/or BAR2 (secondary channel). To exemplify:
// BAR0 + 0 is first port.
// BAR0 + 1 is second port.
// BAR0 + 2 is the third

#define ATA_REG_DATA       0x00
#define ATA_REG_ERROR      0x01
#define ATA_REG_FEATURES   0x01
#define ATA_REG_SECCOUNT0  0x02
#define ATA_REG_LBA0       0x03
#define ATA_REG_LBA1       0x04
#define ATA_REG_LBA2       0x05
#define ATA_REG_HDDEVSEL   0x06
#define ATA_REG_COMMAND    0x07
#define ATA_REG_STATUS     0x07
#define ATA_REG_SECCOUNT1  0x08
#define ATA_REG_LBA3       0x09
#define ATA_REG_LBA4       0x0A
#define ATA_REG_LBA5       0x0B
#define ATA_REG_CONTROL    0x0C
#define ATA_REG_ALTSTATUS  0x0C
#define ATA_REG_DEVADDRESS 0x0D

// Channels:
#define      ATA_PRIMARY      0x00
#define      ATA_SECONDARY    0x01
 
// Directions:
#define      ATA_READ      0x00
#define      ATA_WRITE     0x01

// BAR0 is the start of the I/O ports used by the primary channel.
// BAR1 is the start of the I/O ports which control the primary channel.
// BAR2 is the start of the I/O ports used by secondary channel.
// BAR3 is the start of the I/O ports which control secondary channel.
// BAR4 is the start of 8 I/O ports controls the primary channel's Bus Master IDE.
// BAR4 + 8 is the Base of 8 I/O ports controls secondary channel's Bus Master IDE.

uint8 ide_buf[2048] = {0};
static uint8 ide_irq_invoked = 0;
static uint8 atapi_packet[12] = {0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// We said the the IDE can contain up to 4 drives:
struct ide_device {
   uint8  Reserved;    // 0 (Empty) or 1 (This Drive really exists).
   uint8  Channel;     // 0 (Primary Channel) or 1 (Secondary Channel).
   uint8  Drive;       // 0 (Master Drive) or 1 (Slave Drive).
   uint16 Type;        // 0: ATA, 1:ATAPI.
   uint16 Signature;   // Drive Signature
   uint16 Capabilities;// Features.
   uint32   CommandSets; // Command Sets Supported.
   uint32   Size;        // Size in Sectors.
   uint8  Model[41];   // Model in string.
} ide_devices[4];

struct IDEChannelRegisters {
   uint16 base;  // I/O Base.
   uint16 ctrl;  // Control Base
   uint16 bmide; // Bus Master IDE
   uint8  nIEN;  // nIEN (No Interrupt);
} channels[2];

uint8 ide_read(uint8 channel, uint8 reg) {
   uint8 result;
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
   if (reg < 0x08)
      result = inb(channels[channel].base + reg - 0x00);
   else if (reg < 0x0C)
      result = inb(channels[channel].base  + reg - 0x06);
   else if (reg < 0x0E)
      result = inb(channels[channel].ctrl  + reg - 0x0A);
   else if (reg < 0x16)
      result = inb(channels[channel].bmide + reg - 0x0E);
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
   return result;
}

void ide_write(uint8 channel, uint8 reg, uint8 data) {
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
   if (reg < 0x08)
      outb(channels[channel].base  + reg - 0x00 , data);
   else if (reg < 0x0C)
      outb(channels[channel].base  + reg - 0x06 , data);
   else if (reg < 0x0E)
      outb(channels[channel].ctrl  + reg - 0x0A , data);
   else if (reg < 0x16)
      outb(channels[channel].bmide + reg - 0x0E , data);
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
}

// To read the identification space, we should read the Data Register as a double word 128 times. We can then copy them to our buffer.
void ide_read_buffer(uint8 channel, uint8 reg, uint32 buffer, uint32 quads) {
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
   asm("pushw %es; movw %ds, %ax; movw %ax, %es");
   if (reg < 0x08)
      insl(channels[channel].base  + reg - 0x00, (void *)buffer, quads);
   else if (reg < 0x0C)
      insl(channels[channel].base  + reg - 0x06, (void *)buffer, quads);
   else if (reg < 0x0E)
      insl(channels[channel].ctrl  + reg - 0x0A, (void *)buffer, quads);
   else if (reg < 0x16)
      insl(channels[channel].bmide + reg - 0x0E, (void *)buffer, quads);
   asm("popw %es;");
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
}

// When we send a command, we should wait for 400 nanosecond, then read the Status port. If the Busy bit is on, we should read the status port again until the Busy bit is 0; then we can read the results of the command. This operation is called "Polling". We can also use IRQs instead of polling.
// After many commands, if the Device Fault bit is set, there is a failure; if DRQ is not set, there is an error. If the ERR bit is set, there is an error which is described in Error port.
uint8 ide_polling(uint8 channel, uint32 advanced_check) {
 
   // (I) Delay 400 nanosecond for BSY to be set:
   // -------------------------------------------------
	int i = 0;
   for( ; i < 4; i++)
      ide_read(channel, ATA_REG_ALTSTATUS); // Reading the Alternate Status port wastes 100ns; loop four times.
 
   // (II) Wait for BSY to be cleared:
   // -------------------------------------------------
   while (ide_read(channel, ATA_REG_STATUS) & ATA_SR_BSY)
      ; // Wait for BSY to be zero.
 
   if (advanced_check) {
      uint8 state = ide_read(channel, ATA_REG_STATUS); // Read Status Register.
 
      // (III) Check For Errors:
      // -------------------------------------------------
      if (state & ATA_SR_ERR)
         return 2; // Error.
 
      // (IV) Check If Device fault:
      // -------------------------------------------------
      if (state & ATA_SR_DF)
         return 1; // Device Fault.
 
      // (V) Check DRQ:
      // -------------------------------------------------
      // BSY = 0; DF = 0; ERR = 0 so we should check for DRQ now.
      if ((state & ATA_SR_DRQ) == 0)
         return 3; // DRQ should be set
 
   }
 
   return 0; // No Error.
 
}

uint8 ide_print_error(uint32 drive, uint8 err) {
   if (err == 0)
      return err;
 
   printf("IDE:");
   if (err == 1) {printf("- Device Fault\n     "); err = 19;}
   else if (err == 2) {
      uint8 st = ide_read(ide_devices[drive].Channel, ATA_REG_ERROR);
      if (st & ATA_ER_AMNF)   {printf("- No Address Mark Found\n     ");   err = 7;}
      if (st & ATA_ER_TK0NF)   {printf("- No Media or Media Error\n     ");   err = 3;}
      if (st & ATA_ER_ABRT)   {printf("- Command Aborted\n     ");      err = 20;}
      if (st & ATA_ER_MCR)   {printf("- No Media or Media Error\n     ");   err = 3;}
      if (st & ATA_ER_IDNF)   {printf("- ID mark not Found\n     ");      err = 21;}
      if (st & ATA_ER_MC)   {printf("- No Media or Media Error\n     ");   err = 3;}
      if (st & ATA_ER_UNC)   {printf("- Uncorrectable Data Error\n     ");   err = 22;}
      if (st & ATA_ER_BBK)   {printf("- Bad Sectors\n     ");       err = 13;}
   } else  if (err == 3)           {printf("- Reads Nothing\n     "); err = 23;}
     else  if (err == 4)  {printf("- Write Protected\n     "); err = 8;}
   printf("- [%s %s] %s\n",
      (const char *[]){"Primary", "Secondary"}[ide_devices[drive].Channel], // Use the channel as an index into the array
      (const char *[]){"Master", "Slave"}[ide_devices[drive].Drive], // Same as above, using the drive
      ide_devices[drive].Model);
 
   return err;
}

void ide_detect(uint8 bus , uint8 device , uint8 func , uint8 Class , uint8 subclass , uint8 ProgIF ){

	outl(0xCF8 , (1 << 31) | (bus << 16) | (device << 11) | (func << 8) | 8); // Send the parameters.
	if ((inl(0xCFC) >> 16) != 0xFFFF) { // If device exists (class isn't 0xFFFF)
		 // Check if this device needs an IRQ assignment:
		printf("device exists...check if needs an IRQ assignment");
		 outl(0xCF8 , (1 << 31) | (bus << 16) | (device << 11) | (func << 8) | 0x3C); // Read the interrupt line field
		 outb(0xCFC , 0xFE); // Change the IRQ field to 0xFE
		 outl(0xCF8 , (1 << 31) | (bus << 16) | (device << 11) | (func << 8) | 0x3C); // Read the interrupt line field
		 if ((inl(0xCFC) & 0xFF) == 0xFE) {
				printf("This devices needs an IRQ assignment");
		    // This device needs an IRQ assignment.
		 } else {
		    // The device doesn't use IRQs, check if this is an Parallel IDE:
				printf("This device doesn't use IRQs, check if this is a Parallel IDE...");
		    if (Class == 0x01 && subclass == 0x01 && (ProgIF == 0x8A || ProgIF == 0x80)) {
		       // This is a Parallel IDE Controller which uses IRQs 14 and 15.
		    }
		 }
	}

}

void ide_initialize(uint32 BAR0, uint32 BAR1, uint32 BAR2, uint32 BAR3,
uint32 BAR4) {
 
   int i , j , k , count = 0;
 
   // 1- Detect I/O Ports which interface IDE Controller:
   channels[ATA_PRIMARY  ].base  = (BAR0 & 0xFFFFFFFC) + 0x1F0 * (!BAR0);
   channels[ATA_PRIMARY  ].ctrl  = (BAR1 & 0xFFFFFFFC) + 0x3F4 * (!BAR1);
   channels[ATA_SECONDARY].base  = (BAR2 & 0xFFFFFFFC) + 0x170 * (!BAR2);
   channels[ATA_SECONDARY].ctrl  = (BAR3 & 0xFFFFFFFC) + 0x374 * (!BAR3);
   channels[ATA_PRIMARY  ].bmide = (BAR4 & 0xFFFFFFFC) + 0; // Bus Master IDE
   channels[ATA_SECONDARY].bmide = (BAR4 & 0xFFFFFFFC) + 8; // Bus Master IDE

	// Then we should disable IRQs in both channels by setting bit 1 (nIEN) in the Control port:
	// 2- Disable IRQs:
   ide_write(ATA_PRIMARY  , ATA_REG_CONTROL, 2);
   ide_write(ATA_SECONDARY, ATA_REG_CONTROL, 2);

	// Now we need to check for drives which could be connected to each channel. We will select the master drive of each channel, and send the ATA_IDENTIFY command (which is supported by ATA Drives). If there's no error, there are values returned in registers which determine the type of Drive; if no drive is present, there will be strange values.
	// Notice that if bit 4 in HDDEVSEL is set to 1, we are selecting the slave drive, if set to 0, we are selecting the master drive.	
	// 3- Detect ATA-ATAPI Devices:
   for (i = 0 ; i < 2; i++)
      for (j = 0; j < 2; j++) {
 
         uint8 err = 0, type = IDE_ATA, status;
         ide_devices[count].Reserved = 0; // Assuming that no drive here.
 
         // (I) Select Drive:
         ide_write(i, ATA_REG_HDDEVSEL, 0xA0 | (j << 4)); // Select Drive.
         sleep(1); // Wait 1ms for drive select to work.
 
         // (II) Send ATA Identify Command:
         ide_write(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
         sleep(1); // This function should be implemented in your OS. which waits for 1 ms.
                   // it is based on System Timer Device Driver.
 
         // (III) Polling:
			//		printf("start polling...");
         if (ide_read(i, ATA_REG_STATUS) == 0) continue; // If Status = 0, No Device.
 
         while(1) {
            status = ide_read(i, ATA_REG_STATUS);
            if ((status & ATA_SR_ERR)) {err = 1; break;} // If Err, Device is not ATA.
            if (!(status & ATA_SR_BSY) && (status & ATA_SR_DRQ)) break; // Everything is right.
         }
 
         // (IV) Probe for ATAPI Devices: 
         if (err != 0) {
            uint8 cl = ide_read(i, ATA_REG_LBA1);
            uint8 ch = ide_read(i, ATA_REG_LBA2);
 
            if (cl == 0x14 && ch ==0xEB)
               type = IDE_ATAPI;
            else if (cl == 0x69 && ch == 0x96)
               type = IDE_ATAPI;
            else{
							printf("Unknown device type!");
               continue; // Unknown Type (may not be a device).
						}
 
            ide_write(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY_PACKET);
            sleep(1);
         }

		//		printf("type=%b",type);
 
         // (V) Read Identification Space of the Device:
         ide_read_buffer(i, ATA_REG_DATA, (uint32) ide_buf, 128);
 
         // (VI) Read Device Parameters:
         ide_devices[count].Reserved     = 1;
         ide_devices[count].Type         = type;
         ide_devices[count].Channel      = i;
         ide_devices[count].Drive        = j;
         ide_devices[count].Signature    = ((uint16 )(ide_buf + ATA_IDENT_DEVICETYPE));
         ide_devices[count].Capabilities = ((uint16 )(ide_buf + ATA_IDENT_CAPABILITIES));
         ide_devices[count].CommandSets  = ((uint32 )(ide_buf + ATA_IDENT_COMMANDSETS));
 
         // (VII) Get Size:
         if (ide_devices[count].CommandSets & (1 << 26))
            // Device uses 48-Bit Addressing:
            ide_devices[count].Size   = ((uint32 )(ide_buf + ATA_IDENT_MAX_LBA_EXT));
         else
            // Device uses CHS or 28-bit Addressing:
            ide_devices[count].Size   = ((uint32 )(ide_buf + ATA_IDENT_MAX_LBA));
//  				printf("size=%ui",(uint32)ide_devices[count].Size);
         // (VIII) String indicates model of device (like Western Digital HDD and SONY DVD-RW...):
         for(k = 0; k < 40; k += 2) {
            ide_devices[count].Model[k] = ide_buf[ATA_IDENT_MODEL + k + 1];
            ide_devices[count].Model[k + 1] = ide_buf[ATA_IDENT_MODEL + k];}
         ide_devices[count].Model[40] = 0; // Terminate String.
 
         count++;
      }
 
   // 4- Print Summary:
   for (i = 0; i < 4; i++)
      if (ide_devices[i].Reserved == 1) {
         printf(" Found %s Drive %uiGB - %s\n",
            (const char *[]){"ATA", "ATAPI"}[ide_devices[i].Type],         /* Type */
            ide_devices[i].Size / 1024 / 1024 / 2,               /* Size */
            ide_devices[i].Model);
      }
}
	

/*******************************************************************************
* FUNCTION: ide_read_sectors
*
* PURPOSE: to read from an ATA device
*
* PARAMETERS:
*
* RETURN: 
*
* SIDE EFFECTS:
********************************************************************************/
void ide_read_sectors(uint8 drive, uint8 numsects, uint32 lba,
                      uint16 es, uint32 edi) {
 
   // 1: Check if the drive presents:
   // ==================================
	if (drive > 3 || ide_devices[drive].Reserved == 0){
		// package[0] = 0x1;      // Drive Not Found!
		printf("Drive not found!");
	}
 
   // 2: Check if inputs are valid:
   // ==================================
  else if (((lba + numsects) > ide_devices[drive].Size) && (ide_devices[drive].Type == IDE_ATA)){
  	// package[0] = 0x2;                     // Seeking to invalid position.
		printf("Seeking to invalid position");
	}
 
   // 3: Read in PIO Mode through Polling & IRQs:
   // ============================================
   else {
      uint8 err;
      if (ide_devices[drive].Type == IDE_ATA)
         err = ide_ata_access(ATA_READ, drive, lba, numsects, es, edi);
      else if (ide_devices[drive].Type == IDE_ATAPI){
				int i = 0;
         for ( ; i < numsects; i++)
            err = ide_atapi_read(drive, lba + i, 1, es, edi + (i*2048));
			}
      // package[0] = ide_print_error(drive, err);
			ide_print_error(drive, err);			
   }
}
// package[0] is an entry of an array. It contains the Error Code.

void ide_wait_irq(void) {
   while (!ide_irq_invoked)
      ;
   ide_irq_invoked = 0;
}

void ide_irq(void) {
   ide_irq_invoked = 1;
}

/*******************************************************************************
* FUNCTION: ide_atapi_read
*
* PURPOSE: to read from an ATAPI device
*
* PARAMETERS:
*
* RETURN: 
*
* SIDE EFFECTS:
********************************************************************************/
uint8 ide_atapi_read(uint8 drive, uint32 lba, uint8 numsects,uint16 selector, uint32 edi) {
	uint32   channel  = ide_devices[drive].Channel;
   uint32   slavebit = ide_devices[drive].Drive;
   uint32   bus      = channels[channel].base;
   uint32   words    = 1024; // Sector Size. ATAPI drives have a sector size of 2048 bytes.
   uint8  err;
   int i = 0;

	// Enable IRQs:
   ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN = ide_irq_invoked = 0x0);

	// (I): Setup SCSI Packet:
   // ------------------------------------------------------------------
   atapi_packet[ 0] = ATAPI_CMD_READ;
   atapi_packet[ 1] = 0x0;
   atapi_packet[ 2] = (lba >> 24) & 0xFF;
   atapi_packet[ 3] = (lba >> 16) & 0xFF;
   atapi_packet[ 4] = (lba >> 8) & 0xFF;
   atapi_packet[ 5] = (lba >> 0) & 0xFF;
   atapi_packet[ 6] = 0x0;
   atapi_packet[ 7] = 0x0;
   atapi_packet[ 8] = 0x0;
   atapi_packet[ 9] = numsects;
   atapi_packet[10] = 0x0;
   atapi_packet[11] = 0x0;

	// (II): Select the drive:
   // ------------------------------------------------------------------
   ide_write(channel, ATA_REG_HDDEVSEL, slavebit << 4);

	// (III): Delay 400 nanoseconds for select to complete:
   // ------------------------------------------------------------------
   for( ; i < 4; i++)
       ide_read(channel, ATA_REG_ALTSTATUS); // Reading the Alternate Status port wastes 100ns.

	// (IV): Inform the Controller that we use PIO mode:
   // ------------------------------------------------------------------
   ide_write(channel, ATA_REG_FEATURES, 0);         // PIO mode.

	// (V): Tell the Controller the size of buffer:
   // ------------------------------------------------------------------
   ide_write(channel, ATA_REG_LBA1, (words * 2) & 0xFF);   // Lower Byte of Sector Size.
   ide_write(channel, ATA_REG_LBA2, (words * 2) >> 8);   // Upper Byte of Sector Size.

	// (VI): Send the Packet Command:
   // ------------------------------------------------------------------
   ide_write(channel, ATA_REG_COMMAND, ATA_CMD_PACKET);      // Send the Command.
 
   // (VII): Waiting for the driver to finish or return an error code:
   // ------------------------------------------------------------------
   if ( (err = ide_polling(channel, 1)) != 0 ) return err;         // Polling and return if error.
 
   // (VIII): Sending the packet data:
   // ------------------------------------------------------------------
   asm("rep   outsw" : : "c"(6), "d"(bus), "S"(atapi_packet));   // Send Packet Data

	// (IX): Receiving Data:
   // ------------------------------------------------------------------
   for (i = 0; i < numsects; i++) {
      ide_wait_irq();                  // Wait for an IRQ.
      if ( (err = ide_polling(channel, 1)) != 0 )
         return err;      // Polling and return if error.
      asm("pushw %es");
      asm("mov %%ax, %%es"::"a"(selector));
      asm("rep insw"::"c"(words), "d"(bus), "D"(edi));// Receive Data.
      asm("popw %es");
      edi += (words * 2);
   }

	// (X): Waiting for an IRQ:
   // ------------------------------------------------------------------
   ide_wait_irq();
 
   // (XI): Waiting for BSY & DRQ to clear:
   // ------------------------------------------------------------------
   while (ide_read(channel, ATA_REG_STATUS) & (ATA_SR_BSY | ATA_SR_DRQ))
      ;
 
   return 0; // Easy, ... Isn't it?
}

/*******************************************************************************
* FUNCTION: ide_write_sectors
*
* PURPOSE: to write to an ATA device
*
* PARAMETERS:
*
* RETURN: 
*
* SIDE EFFECTS:
********************************************************************************/
void ide_write_sectors(uint8 drive, uint8 numsects, uint32 lba,
                       uint16 es, uint32 edi) {
 
   // 1: Check if the drive presents:
   // ==================================
   if (drive > 3 || ide_devices[drive].Reserved == 0){
      // package[0] = 0x1;      // Drive Not Found!
		printf("Drive not found!");
	}
   // 2: Check if inputs are valid:
   // ==================================
   else if (((lba + numsects) > ide_devices[drive].Size) && (ide_devices[drive].Type == IDE_ATA)){
      // package[0] = 0x2;                     // Seeking to invalid position.
		printf("seeking to invalid position");
		}
   // 3: Read in PIO Mode through Polling & IRQs:
   // ============================================
   else {
      uint8 err;
      if (ide_devices[drive].Type == IDE_ATA)
         err = ide_ata_access(ATA_WRITE, drive, lba, numsects, es, edi);
      else if (ide_devices[drive].Type == IDE_ATAPI)
         err = 4; // Write-Protected.
      //package[0] = ide_print_error(drive, err);
			ide_print_error(drive, err);
   }
}

/*******************************************************************************
* FUNCTION: ide_ata_access
*
* PURPOSE: to read/write from/to an ATA device
*
* PARAMETERS:
*
* RETURN: 
*
* SIDE EFFECTS:
********************************************************************************/
uint8 ide_ata_access(uint8 direction, uint8 drive, uint32 lba, 
	uint8 numsects, uint16 selector, uint32 edi)
{
	uint8 lba_mode /* 0: CHS, 1:LBA28, 2: LBA48 */, dma /* 0: No DMA, 1: DMA */, cmd;
  uint8 lba_io[6];
	uint32  channel      = ide_devices[drive].Channel; // Read the Channel.
  uint32  slavebit      = ide_devices[drive].Drive; // Read the Drive [Master/Slave]
  uint32  bus = channels[channel].base; // Bus Base, like 0x1F0 which is also data port.
  uint32  words      = 256; // Almost every ATA drive has a sector-size of 512-byte.
  uint16 cyl, i;
  uint8 head, sect, err;
	
	// disable IRQs on all drives
	ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN = (ide_irq_invoked = 0x0) + 0x02);

	// Read the parameters //

	// (I) Select one from LBA28, LBA48 or CHS;
   if (lba >= 0x10000000) { // Sure Drive should support LBA in this case, or you are
                            // giving a wrong LBA.
      // LBA48:
      lba_mode  = 2;
      lba_io[0] = (lba & 0x000000FF) >> 0;
      lba_io[1] = (lba & 0x0000FF00) >> 8;
      lba_io[2] = (lba & 0x00FF0000) >> 16;
      lba_io[3] = (lba & 0xFF000000) >> 24;
      lba_io[4] = 0; // LBA28 is integer, so 32-bits are enough to access 2TB.
      lba_io[5] = 0; // LBA28 is integer, so 32-bits are enough to access 2TB.
      head      = 0; // Lower 4-bits of HDDEVSEL are not used here.
   } else if (ide_devices[drive].Capabilities & 0x200)  { // Drive supports LBA?
      // LBA28:
      lba_mode  = 1;
      lba_io[0] = (lba & 0x00000FF) >> 0;
      lba_io[1] = (lba & 0x000FF00) >> 8;
      lba_io[2] = (lba & 0x0FF0000) >> 16;
      lba_io[3] = 0; // These Registers are not used here.
      lba_io[4] = 0; // These Registers are not used here.
      lba_io[5] = 0; // These Registers are not used here.
      head      = (lba & 0xF000000) >> 24;
   } else {
      // CHS:
      lba_mode  = 0;
      sect      = (lba % 63) + 1;
      cyl       = (lba + 1  - sect) / (16 * 63);
      lba_io[0] = sect;
      lba_io[1] = (cyl >> 0) & 0xFF;
      lba_io[2] = (cyl >> 8) & 0xFF;
      lba_io[3] = 0;
      lba_io[4] = 0;
      lba_io[5] = 0;
      head      = (lba + 1  - sect) % (16 * 63) / (63); // Head number is written to HDDEVSEL lower 4-bits.
   }

	// Now we are going to choose the way of reading the buffer [PIO or DMA]: //

	// (II) See if drive supports DMA or not;
  dma = 0; // We don't support DMA

	// (III) Wait if the drive is busy;
  while (ide_read(channel, ATA_REG_STATUS) & ATA_SR_BSY)
  	;

	// (IV) Select Drive from the controller;
   if (lba_mode == 0)
      ide_write(channel, ATA_REG_HDDEVSEL, 0xA0 | (slavebit << 4) | head); // Drive & CHS.
   else
      ide_write(channel, ATA_REG_HDDEVSEL, 0xE0 | (slavebit << 4) | head); // Drive & LBA

	// (V) Write Parameters;
   if (lba_mode == 2) {
      ide_write(channel, ATA_REG_SECCOUNT1,   0);
      ide_write(channel, ATA_REG_LBA3,   lba_io[3]);
      ide_write(channel, ATA_REG_LBA4,   lba_io[4]);
      ide_write(channel, ATA_REG_LBA5,   lba_io[5]);
   }
   ide_write(channel, ATA_REG_SECCOUNT0,   numsects);
   ide_write(channel, ATA_REG_LBA0,   lba_io[0]);
   ide_write(channel, ATA_REG_LBA1,   lba_io[1]);
   ide_write(channel, ATA_REG_LBA2,   lba_io[2]);

	// Now, we have a great set of commands described in ATA/ATAPI-8 Specification, we should choose the suitable command to execute:
	// (VI) Select the command and send it;
   // Routine that is followed:
   // If ( DMA & LBA48)   DO_DMA_EXT;
   // If ( DMA & LBA28)   DO_DMA_LBA;
   // If ( DMA & LBA28)   DO_DMA_CHS;
   // If (!DMA & LBA48)   DO_PIO_EXT;
   // If (!DMA & LBA28)   DO_PIO_LBA;
   // If (!DMA & !LBA#)   DO_PIO_CHS;

	// There isn't a command for doing CHS with DMA
	if (lba_mode == 0 && dma == 0 && direction == 0) cmd = ATA_CMD_READ_PIO;
	if (lba_mode == 1 && dma == 0 && direction == 0) cmd = ATA_CMD_READ_PIO;   
	if (lba_mode == 2 && dma == 0 && direction == 0) cmd = ATA_CMD_READ_PIO_EXT;   
	if (lba_mode == 0 && dma == 1 && direction == 0) cmd = ATA_CMD_READ_DMA;
	if (lba_mode == 1 && dma == 1 && direction == 0) cmd = ATA_CMD_READ_DMA;
	if (lba_mode == 2 && dma == 1 && direction == 0) cmd = ATA_CMD_READ_DMA_EXT;
	if (lba_mode == 0 && dma == 0 && direction == 1) cmd = ATA_CMD_WRITE_PIO;
	if (lba_mode == 1 && dma == 0 && direction == 1) cmd = ATA_CMD_WRITE_PIO;
	if (lba_mode == 2 && dma == 0 && direction == 1) cmd = ATA_CMD_WRITE_PIO_EXT;
	if (lba_mode == 0 && dma == 1 && direction == 1) cmd = ATA_CMD_WRITE_DMA;
	if (lba_mode == 1 && dma == 1 && direction == 1) cmd = ATA_CMD_WRITE_DMA;
	if (lba_mode == 2 && dma == 1 && direction == 1) cmd = ATA_CMD_WRITE_DMA_EXT;
	ide_write(channel, ATA_REG_COMMAND, cmd);               // Send the Command.

	// After sending the command, we should poll, then we read/write a sector, then we should poll, then we read/write a sector, until we read/write all sectors needed, if an error has happened, the function will return a specific error code.
	// Notice that after writing, we should execute the CACHE FLUSH command, and we should poll after it, but without checking for errors.
		
	if (dma)
      if (direction == 0){
         // DMA Read.				
				printf("should be doing a DMA read here");
			}
      else{
         // DMA Write.
				printf("should be doing a DMA write here");
		}
   else
      if (direction == 0)
         // PIO Read.
      for (i = 0; i < numsects; i++) {
         if ( (err = ide_polling(channel, 1)) != 0 )
            return err; // Polling, set error and exit if there is.
         asm("pushw %es");
         asm("mov %%ax, %%es" : : "a"(selector));
         asm("rep insw" : : "c"(words), "d"(bus), "D"(edi)); // Receive Data.
         asm("popw %es");
         edi += (words*2);
      } else {
      // PIO Write.
         for (i = 0; i < numsects; i++) {
            ide_polling(channel, 0); // Polling.
            asm("pushw %ds");
            asm("mov %%ax, %%ds"::"a"(selector));
            asm("rep outsw"::"c"(words), "d"(bus), "S"(edi)); // Send Data
            asm("popw %ds");
            edi += (words*2);
         }
         ide_write(channel, ATA_REG_COMMAND, (char []) {   ATA_CMD_CACHE_FLUSH,
                        ATA_CMD_CACHE_FLUSH,
                        ATA_CMD_CACHE_FLUSH_EXT}[lba_mode]);
         ide_polling(channel, 0); // Polling.
      }
 
   return 0; // Easy, isn't it?
}


