// contains wrapper functions for misc assembly functions

.globl load_IDT
		
load_IDT:
	cli
	movl 4(%esp) , %eax
	lidt (%eax)
	sti
	ret

