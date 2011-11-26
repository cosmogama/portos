#include "interrupts_private.h"
#include "gdt.h"

///////////////  IDT stuff

const int max_interrupts = 256;
IDTR idtr;
IDT_entry idt[256];
static void idt_set_gate(int, uint16, uint8, uint32);

/* defined in idt-asm.s */
extern void load_IDT(uint32);
/* defined in isr_stubs.s */
extern void isr_stub(void);
extern void isr_stub_kbd(void);

void init_IDT(void)  {

	int i = 0;
	for( ; i<max_interrupts; i++ ){
		if( i == KBD_IRQ )
 			idt_set_gate(i, KERNEL_CS, INTERRUPT_FLAGS, (uint32)isr_stub_kbd);
		else
			idt_set_gate(i, KERNEL_CS, INTERRUPT_FLAGS, (uint32)isr_stub);
  }

  idtr.limit = sizeof(IDT_entry) * max_interrupts - 1;
  idtr.offset = (uint32)(&idt);

	load_IDT(((uint32)&idtr));
  
}

static void idt_set_gate(int num, uint16 selector, uint8 flags, uint32 handler) {
  idt[num].zero = 0;
  idt[num].flags = flags;
  idt[num].selector = selector;
  idt[num].base_lo = handler & 0xFFFF;
  idt[num].base_hi = (handler >> 16) & 0xFFFF;
}
