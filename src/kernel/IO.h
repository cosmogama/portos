#ifndef _IO_H
#define _IO_H

__inline__ void outportb(unsigned short port, unsigned char val);
__inline__ unsigned char inportb(unsigned short port);
__inline__ void io_wait(void);

#endif
