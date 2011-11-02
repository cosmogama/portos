#if RUN_TESTS == true

#include "message_printer.h"
#include "printf.h"
#include "monitor.h"
#include "assert.h"
#include "string.h"

void t_printf_3_1_1(){
	puts("|3.1.*|");
		
	char out[200];
	char * arg1 = "ladida";
	char * arg2 = "hahaha";
	char * arg3 = "lololo";
	char * format = "string %s after string %s after string %s\n";
	char * expected = "string ladida after string hahaha after string lololo\n";

	sprintf(out , format , arg1 , arg2 , arg3);
	//puts( "out=" ); puts(out); putc(' ');
	//puts( "expected=" ); puts(expected); putc(' ');
	assert( strcmp(out,expected) == 0 );
}

void t_printf_3_1_2(){
	puts("|");
		
	char out[200];
	int arg1 = 123;
	long arg2 = 456;
	short arg3 = 789;
	int arg4 = 111;
	char * format = "here %i and there %l and here %o and there %h\n";
	char * expected = "here 123 and there 456 and here 789 and there 0x0000006F\n";

	sprintf(out , format , arg1 , arg2 , arg3 , arg4);
	//puts( "out=" ); puts(out); putc(' ');
	//puts( "expected=" ); puts(expected); putc(' ');
	assert( strcmp(out,expected) == 0 );
}

void t_printf_3_1_3(){
	puts("|");
		
	char out[200];
	int arg1 = 1;
	long arg2 = 2;
	short arg3 = 3;
	BYTE arg4 = 4;
	char arg5 = 'g';
	char arg6 = 'h';
	char arg7 = 'i';
	char arg8 = 'j';
	char * format = "%i%ul%o%b%c%c%c%c\n";
	char * expected = "1234ghij\n";

	sprintf(out , format , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8);
	//puts( "out=" ); puts(out); putc(' ');
	//puts( "expected=" ); puts(expected); putc(' ');
	assert( strcmp(out,expected) == 0 );
}

void t_printf2(){
	puts("<printf2>");
	t_printf_3_1_1();
	t_printf_3_1_2();
	t_printf_3_1_3();
}

#endif
