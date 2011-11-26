#ifndef _INTERRUPTS_PRIVATE_H
#define _INTERRUPTS_PRIVATE_H

//***************************************************************
// INCLUDES
//***************************************************************
#include "types.h"

//***************************************************************
// CONSTANTS / SETTINGS
//***************************************************************

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

// 
#define   SEL 0x40

#define		INTERRUPT_FLAGS		0x8E
#define		TRAP_FLAGS		0x8F

#define		MAX_INTERRUPTS		256

//***************************************************************
// TYPES
//***************************************************************
struct idt_entry {
  WORD base_lo;
  WORD selector;
  BYTE zero;
  BYTE flags;
  WORD base_hi;
} __attribute__((packed));
typedef struct idt_entry IDT_entry;

struct _IDTR {
  WORD limit;
  DWORD offset;
} __attribute__((packed));
typedef struct _IDTR IDTR;

#endif

