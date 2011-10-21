
__inline__ void 
outportb(unsigned short port, unsigned char val)
{
   asm volatile("outb %0,%1"::"a"(val), "Nd" (port));
}

__inline__ unsigned char 
inportb(unsigned short port)
{
   unsigned char ret;
   asm volatile ("inb %1,%0":"=a"(ret):"Nd"(port));
   return ret;
}

__inline__ void 
io_wait(void)
{
   asm volatile("jmp 1f;1:jmp 1f;1:");
}
