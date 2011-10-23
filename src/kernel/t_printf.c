#include "printf.h"

void t_printf_1_1_1(){
	printf("this is a test\n");
	printf("this is a test %s\n","and another test");
	printf("this is a test %h\n",20);
	printf("this is a test %u\n",-1);
	printf("this is a test %u %u\n",-1,20);
	printf("this is a test %u %i %h\n",-1,-1,-1);
}

void t_printf(){
	t_printf_1_1_1();
}
