// ;;; this file just contains the isr stubs that are installed from 
// ;;; interrupts.c. The stubs just push values, call the appropriate
// ;;; function which is defined in interrupts.c, pop values and
// ;;; execute an iret

.globl handle_interrupt
.globl isr_stub

	isr_stub:
	cli
	pusha
	call handle_interrupt
	popa
	
	sti
	iret

.globl handle_interrupt_kbd
.globl isr_stub_kbd

	isr_stub_kbd:
	cli
	pusha
	call handle_interrupt_kbd
	popa
	
	sti
	iret

