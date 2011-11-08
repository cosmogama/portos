#ifndef _IDT_H
#define _IDT_H

#include "types.h"
#include "interrupts.h"

#define   SEL 0x40

#define		INTERRUPT_FLAGS		0x8E
#define		TRAP_FLAGS		0x8F

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

//***************************************************************
// FUNCTIONS
//***************************************************************

void init_IDT(void);

#endif
