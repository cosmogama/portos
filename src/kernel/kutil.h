#ifndef _KUTIL_H
#define _KUTIL_H

#define asm_enable_intr() asm volatile("sti")
#define asm_disable_intr() asm volatile("cli")

void wait_for_user_input(void);
void sleep( unsigned long milliseconds );
void halt_cpu(void);

#endif
