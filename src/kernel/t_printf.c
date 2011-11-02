#if RUN_TESTS == true

#include "message_printer.h"
#include "printf.h"
#include "monitor.h"
#include "assert.h"
#include "string.h"

void t_printf_2_1_1(){
	puts("|2.1.*|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	char * format = "I'm a string.";
	char * expected = format;

	sprintf(out , format);
	//puts("out="); puts(out); putc(' ');
	//puts("expected="); puts(expected); putc(' ');
	assert( strcmp(out,expected) == 0 );
}

void t_printf_2_1_2(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	char * format = "a";
	char * expected = "a";

	sprintf(out , format);
	//puts("out="); puts(out); putc(' ');
	//puts("expected="); puts(expected); putc(' ');
	assert( strcmp(out,expected) == 0 );
}

void t_printf_2_1_3(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	char * arg1 = NULL;
	char * format = "a string=%s";
	char * expected = "a string=(null)";

	sprintf(out , format , arg1);
	//puts("out="); puts(out); putc(' ');
	//puts("expected="); puts(expected); putc(' ');
	assert( strcmp(out,expected) == 0 );
}

void t_printf_2_1_4(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	BYTE arg1 = -34;
	char * format = "the arg=%b\n";
	char * expected = "the arg=-34\n";

	sprintf( out , format , arg1 );
	//puts( "out=" ); puts(out); putc(' ');
	//puts( "expected=" ); puts(expected); putc(' ');
	assert( strcmp( out , expected ) == 0 );
}

void t_printf_2_1_5(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	char arg1 = 'Q';
	char * format = "the arg=%c\n";
	char * expected = "the arg=Q\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , expected ) == 0 );
}

void t_printf_2_1_6(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	short arg1 = -3456;
	char * format = "the arg=%o\n";
	char * expected = "the arg=-3456\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , expected ) == 0 );
}

void t_printf_2_1_7(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	int arg1 = -13467534;
	char * format = "an int=%i here\n";
	char * expected = "an int=-13467534 here\n";

	sprintf( out , format , arg1 );
	//puts( "out=" ); puts(out); putc(' ');
	//puts( "expected=" ); puts(expected); putc(' ');
	assert( strcmp( out , expected ) == 0 );
}

void t_printf_2_1_8(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	long arg1 = -13467534;
	char * format = "the arg=%l\n";
	char * expected = "the arg=-13467534\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , expected ) == 0 );
}

void t_printf_2_1_9(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	uint64 arg1 = -134675341234124LL;
	char * format = "the arg=%j\n";
	char * expected = "the arg=-134675341234124\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , expected ) == 0 );
}

void t_printf_2_1_10(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	UBYTE arg1 = 255;
	char * format = "the arg=%ub\n";
	char * expected = "the arg=255\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , expected ) == 0 );
}

void t_printf_2_1_11(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	uint16 arg1 = 65535;
	char * format = "the arg=%uo\n";
	char * expected = "the arg=65535\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , expected ) == 0 );
}

void t_printf_2_1_12(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	uint32 arg1 = 4294967295U;
	char * format = "the arg=%ui\n";
	char * expected = "the arg=4294967295\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , expected ) == 0 );
}

void t_printf_2_1_13(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	unsigned long arg1 = 4294967295UL;
	char * format = "the arg=%ul\n";
	char * expected = "the arg=4294967295\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , expected ) == 0 );
}

void t_printf_2_1_14(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	uint64 arg1 = 4294967296ULL;
	char * format = "the arg=%ul\n";
	char * expected = "the arg=4294967296\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , expected ) == 0 );
}

void t_printf_2_1_15(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	uint32 arg1 = 571920;
	char * format = "the arg=%h\n";
	char * expected = "the arg=0x0008BA10\n";

	sprintf( out , format , arg1 );
	//puts( "out=" ); puts(out); putc(' ');
	//puts( "expected=" ); puts(expected); putc(' ');
	assert( strcmp( out , expected ) == 0 );
}

void t_printf_2_1_16(){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	char * arg1 = "another string";
	char * format = "the arg=%s\n";
	char * expected = "the arg=another string\n";

	sprintf( out , format , arg1 );
	//puts( "out=" ); puts(out); putc(' ');
	//puts( "expected=" ); puts(expected); putc(' ');
	assert( strcmp( out , expected ) == 0 );
}

void t_printf(){
	puts("<printf>");
	t_printf_2_1_1();
	t_printf_2_1_2();
	t_printf_2_1_3();
	t_printf_2_1_4();
	t_printf_2_1_5();
	t_printf_2_1_6();
	t_printf_2_1_7();
	t_printf_2_1_8();
	//t_printf_2_1_9();
	t_printf_2_1_10();
	t_printf_2_1_11();
	t_printf_2_1_12();
	t_printf_2_1_13();
	//t_printf_2_1_14();
	t_printf_2_1_15();
	t_printf_2_1_16();
}

#endif
