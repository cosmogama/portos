#include "message_printer.h"
#include "printf.h"
#include "monitor.h"
#include "assert.h"
#include "string.h"

void t_printf_2_1_1(void){
	puts("|2.1.*|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	const const char * format = "I'm a string.";
	const const char * expected = format;

	sprintf(out , format);
	//puts("out="); puts(out); putc(' ');
	//puts("expected="); puts(expected); putc(' ');
	assert( strcmp(out,(char*)expected) == 0 );
}

void t_printf_2_1_2(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	const char * format = "a";
	const char * expected = "a";

	sprintf(out , format);
	//puts("out="); puts(out); putc(' ');
	//puts("expected="); puts(expected); putc(' ');
	assert( strcmp(out,(char *)expected) == 0 );
}

void t_printf_2_1_3(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	char * arg1 = NULL;
	const char * format = "a string=%s";
	const char * expected = "a string=(null)";

	sprintf(out , format , arg1);
	//puts("out="); puts(out); putc(' ');
	//puts("expected="); puts(expected); putc(' ');
	assert( strcmp(out,(char *)expected) == 0 );
}

void t_printf_2_1_4(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	BYTE arg1 = -34;
	const char * format = "the arg=%b\n";
	const char * expected = "the arg=-34\n";

	sprintf( out , format , arg1 );
	//puts( "out=" ); puts(out); putc(' ');
	//puts( "expected=" ); puts(expected); putc(' ');
	assert( strcmp( out , (char *)expected ) == 0 );
}

void t_printf_2_1_5(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	char arg1 = 'Q';
	const char * format = "the arg=%c\n";
	const char * expected = "the arg=Q\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , (char *)expected ) == 0 );
}

void t_printf_2_1_6(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	short arg1 = -3456;
	const char * format = "the arg=%o\n";
	const char * expected = "the arg=-3456\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , (char *)expected ) == 0 );
}

void t_printf_2_1_7(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	int arg1 = -13467534;
	const char * format = "an int=%i here\n";
	const char * expected = "an int=-13467534 here\n";

	sprintf( out , format , arg1 );
	//puts( "out=" ); puts(out); putc(' ');
	//puts( "expected=" ); puts(expected); putc(' ');
	assert( strcmp( out , (char *)expected ) == 0 );
}

void t_printf_2_1_8(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	long arg1 = -13467534;
	const char * format = "the arg=%l\n";
	const char * expected = "the arg=-13467534\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , (char *)expected ) == 0 );
}

void t_printf_2_1_9(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	uint64 arg1 = -134675341234124LL;
	const char * format = "the arg=%j\n";
	const char * expected = "the arg=-134675341234124\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , (char *)expected ) == 0 );
}

void t_printf_2_1_10(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	UBYTE arg1 = 255;
	const char * format = "the arg=%ub\n";
	const char * expected = "the arg=255\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , (char *)expected ) == 0 );
}

void t_printf_2_1_11(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	uint16 arg1 = 65535;
	const char * format = "the arg=%uo\n";
	const char * expected = "the arg=65535\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , (char *)expected ) == 0 );
}

void t_printf_2_1_12(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	uint32 arg1 = 4294967295U;
	const char * format = "the arg=%ui\n";
	const char * expected = "the arg=4294967295\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , (char *)expected ) == 0 );
}

void t_printf_2_1_13(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	unsigned long arg1 = 4294967295UL;
	const char * format = "the arg=%ul\n";
	const char * expected = "the arg=4294967295\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , (char *)expected ) == 0 );
}

void t_printf_2_1_14(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	uint64 arg1 = 4294967296ULL;
	const char * format = "the arg=%ul\n";
	const char * expected = "the arg=4294967296\n";

	sprintf( out , format , arg1 );
	assert( strcmp( out , (char *)expected ) == 0 );
}

void t_printf_2_1_15(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	uint32 arg1 = 571920;
	const char * format = "the arg=%h\n";
	const char * expected = "the arg=0x0008BA10\n";

	sprintf( out , format , arg1 );
	//puts( "out=" ); puts(out); putc(' ');
	//puts( "expected=" ); puts(expected); putc(' ');
	assert( strcmp( out , (char *)expected ) == 0 );
}

void t_printf_2_1_16(void){
	puts("|");
		
	char buff[200];
	char * out = (char *)&buff[0];
	const char * arg1 = "another string";
	const char * format = "the arg=%s\n";
	const char * expected = "the arg=another string\n";

	sprintf( out , format , arg1 );
	//puts( "out=" ); puts(out); putc(' ');
	//puts( "expected=" ); puts(expected); putc(' ');
	assert( strcmp( out , (char *)expected ) == 0 );
}

void t_printf(void){
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

