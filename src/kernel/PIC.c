/*
*
* Device: 8259A [P]rogrammable [I]nterrupt [C]ontroller
* Function: The function of the 8259A is to manage hardware interrupts and send them to the appropriate system interrupt 
* Note: It is important to note that APIC has replaced the 8259 PIC in more modern systems, especially those with multiple cores/processors.
*/

#include "PIC.h"
#include "IO.h"
#include "types.h"

// ****************** FUNCTIONS **********************************

/* In protected mode, the IRQs 0 to 7 conflict with the CPU exception which are reserved by Intel up until 0x1F. (It was an IBM design mistake.) Consequently it is difficult to tell the difference between an IRQ or an software error. It is thus recommended to change the PIC's offsets (also known as remapping the PIC) so that IRQs use non-reserved vectors. A common choice is to move them to the beginning of the available range (IRQs 0..0xF -> INT 0x20..0x2F). For that, we need to set the master PIC's offset to 0x20 and the slave's to 0x28.
*/

/*
arguments:
	offset1 - vector offset for master PIC
		vectors on the master become offset1..offset1+7
	offset2 - same for slave PIC: offset2..offset2+7
*/
void 
PIC_remap(int offset1, int offset2)
{
	unsigned char a1, a2;
 
	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);
 
	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);                 // define the PIC vectors
	io_wait();
	outb(PIC2_DATA, offset2);
	io_wait();
	outb(PIC1_DATA, 4);                       // continue initialization sequence
	io_wait();
	outb(PIC2_DATA, 2);
	io_wait();
 
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();
 
	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);
}

void 
PIC_sendEOI(unsigned char irq)
{
	if(irq >= 8)
		outb(PIC2_COMMAND,PIC_EOI);
 
	outb(PIC1_COMMAND,PIC_EOI);
}

void PIC_initialize(){
	// remap the PIC
	int IRQ0 = 0x20;
	int IRQ8 = 0x28;
	PIC_remap( IRQ0 , IRQ8 );	
	// PIC_remap( IRQ0 , IRQ8 );
	//unsigned char irq_kybd = 1;
	/*
	IRQ_set_mask( irq_kybd );
	IRQ_set_mask( 0 );
	IRQ_set_mask( 2 );
	IRQ_set_mask( 3 );
	IRQ_set_mask( 4 );
	IRQ_set_mask( 5 );
	IRQ_set_mask( 6 );
	IRQ_set_mask( 7 );
	IRQ_set_mask( 8 );
	*/
}

void IRQ_set_mask(unsigned char IRQline) {
    uint16 port;
    uint8 value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) | (1 << IRQline);
    outb(port, value);        
}
 
void IRQ_clear_mask(unsigned char IRQline) {
    uint16 port;
    uint8 value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}
