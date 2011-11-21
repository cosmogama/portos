#ifndef _IO_H
#define _IO_H

#include "types.h"

__inline__ void outb(uint16 port, uint8 val);
__inline__ void outw(uint16 port, uint16 val);
__inline__ void outl(uint16 port, uint32 val);
__inline__ uint8 inb(uint16 port);
__inline__ uint16 inw(uint16 port);
__inline__ uint32 inl(uint16 port);
__inline__ void insl(uint16 port , void * address , int count);
__inline__ void io_wait(void);

#endif
