#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "types.h"

//exception numbers
#define         DIVIDE_ERROR_NO            0
#define         DEBUG_EXCEPTION_NO         1
#define         BREAKPOINT_NO              3
#define         OVERFLOW_NO                4
#define         BOUNDS_CHECK_NO            5
#define         INVALID_OPCODE_NO          6 
#define         NO_COPROCESSOR_NO          7
#define         DOUBLE_FAULT_NO            8
#define         COPROCESSOR_OVERRUN_NO     9
#define         INVALID_TSS_NO             10
#define         SEGMENT_MISSING_NO         11
#define         STACK_EXCEPTION_NO         12
#define         TRIPLE_FAULT_NO            13
#define         PAGE_FAULT_NO              14
#define         CORPROCESSOR_ERROR_NO      16

//irq numbers
#define         TIMER_IRQ               32
#define         KBD_IRQ                 33
#define         FLOPPY_IRQ              38
 
#define		MAX_INTERRUPTS		256

/* initializes interrupt table */
void init_interrupts(void);

#endif
