#include "types.h"

// http://www.cse.iitd.ernet.in/~sbansal/csl373/xv6_html/x86_8h-source.html

__inline__ void 
outb(uint16 port, uint8 val)
{
   asm volatile("outb %0,%1"::"a"(val), "Nd" (port));
}

__inline__ void 
outw(uint16 port, uint16 val)
{
   asm volatile("outw %0,%1"::"a"(val), "Nd" (port));
}

__inline__ void 
outl(uint16 port, uint32 val)
{
   asm volatile("outw %0,%1"::"a"(val), "Nd" (port));
}

__inline__ uint8
inb(uint16 port)
{
   uint8 ret;
   asm volatile ("inb %1,%0":"=a"(ret):"Nd"(port));
   return ret;
}

__inline__ uint16
inw(uint16 port)
{
   uint16 ret;
   asm volatile ("inw %1,%0":"=a"(ret):"Nd"(port));
   return ret;
}

__inline__ uint32
inl(uint16 port)
{
   uint32 ret;
   asm volatile ("inl %1,%0":"=a"(ret):"Nd"(port));
   return ret;
}

__inline__ void 
insl(uint16 port , void * address , int count)
{
	asm volatile("cld; rep insl" :
		"=D" (address), "=c" (count) :
		"d" (port), "0" (address), "1" (count) :
		"memory", "cc");
}

__inline__ void 
io_wait(void)
{
   asm volatile("jmp 1f;1:jmp 1f;1:");
}
