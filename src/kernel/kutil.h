#ifndef _KUTIL_H
#define _KUTIL_H

#define asm_enable_intr() __asm__ ("sti")
#define asm_disable_intr() __asm__ ("cli")

void wait_for_user_input(void);
void sleep( unsigned long milliseconds );
void halt_cpu(void);

#endif
