#include "assert.h"
#include "string.h"
#include "data.h"
#include "monitor.h"

void t_string_1_1_1(){
	puts("|1.1.*|");
	char out[5];
	char * out_next_byte = NULL;
	char * expected = "-103";
	BYTE arg = -103;
	BOOL is_unsigned = FALSE;
	out_next_byte = btoa(out , arg , is_unsigned );
	//puts("out=!"); puts(out); putc('!');
	//puts("expected=!"); puts(expected); putc('!');
	assert( strcmp(out,expected) == 0 );
	assert( out_next_byte == out + 4 );
}

void t_string_1_1_2(){
	puts("|");
	char out[7];
	char * out_next_byte = NULL;
	char * expected = "-10045";
	short sh = -10045;
	BOOL is_unsigned = FALSE;
	out_next_byte = shtoa( out , sh , is_unsigned );
	//puts("out=!"); puts(out); putc('!');
	//puts("expected=!"); puts(expected); putc('!');
	assert( strcmp(out,expected) == 0 );
	assert( out_next_byte == out + 6 );
}

void t_string_1_1_3(){
	puts("|");
	char out[12];
	char * out_next_byte = NULL;
	char * expected = "-1234567";
	int i = -1234567;
	BOOL is_unsigned = FALSE;
	out_next_byte = itoa( out , i , is_unsigned );
	//puts("out=!"); puts(out); putc('!');
	//puts("expected=!"); puts(expected); putc('!');
	assert( strcmp(out,expected) == 0 );
	assert( out_next_byte == out + 8 );
}

void t_string_1_1_4(){
	puts("|");
	char out[12];
	char * out_next_byte = NULL;
	char * expected = "-1234567";
	long l = -1234567;
	BOOL is_unsigned = FALSE;
	out_next_byte = ltoa( out , l , is_unsigned );
	//puts("out=!"); puts(out); putc('!');
	//puts("expected=!"); puts(expected); putc('!');
	assert( strcmp(out,expected) == 0 );
	assert( out_next_byte == out + 8 );
}

void t_string_1_1_5(){
	puts("|");
	char out[21];
	char * out_next_byte = NULL;
	char * expected = "-1234567890";
	int64 i = -1234567890;
	BOOL is_unsigned = FALSE;
	out_next_byte = i64toa( out , i , is_unsigned );
	//puts("out=!"); puts(out); putc('!');
	//puts("expected=!"); puts(expected); putc('!');
	assert( strcmp(out,expected) == 0 );
	assert( out_next_byte == out + 11 );
}

void t_string_1_1_6(){
	puts("|");
	char out[5];
	char * out_next_byte = NULL;
	char * expected = "255";
	UBYTE i = 255;
	BOOL is_unsigned = TRUE;
	out_next_byte = btoa( out , i , is_unsigned );
	//puts("out=!"); puts(out); putc('!');
	//puts("expected=!"); puts(expected); putc('!');
	assert( strcmp(out,expected) == 0 );
	assert( out_next_byte == out + 3 );
}

void t_string_1_1_7(){
	puts("|");
	char out[7];
	char * out_next_byte = NULL;
	char * expected = "65535";
	short sh = 65535;
	BOOL is_unsigned = TRUE;
	out_next_byte = shtoa( out , sh , is_unsigned );
	//puts("out=!"); puts(out); putc('!');
	//puts("expected=!"); puts(expected); putc('!');
	assert( strcmp(out,expected) == 0 );
	assert( out_next_byte == out + 5 );
}

void t_string_1_1_8(){
	puts("|");
	char out[12];
	char * out_next_byte = NULL;
	char * expected = "4294967295";
	uint32 i = 4294967295U;
	BOOL is_unsigned = TRUE;
	out_next_byte = itoa( out , i , is_unsigned );
	//puts("out=!"); puts(out); putc('!');
	//puts("expected=!"); puts(expected); putc('!');
	assert( strcmp(out,expected) == 0 );
	assert( out_next_byte == out + 10 );
}

void t_string_1_1_9(){
	puts("|");
	char out[12];
	char * out_next_byte = NULL;
	char * expected = "4294967295";
	unsigned long l = 4294967295UL;
	BOOL is_unsigned = TRUE;
	out_next_byte = ltoa( out , l , is_unsigned );
	//puts("out=!"); puts(out); putc('!');
	//puts("expected=!"); puts(expected); putc('!');
	assert( strcmp(out,expected) == 0 );
	assert( out_next_byte == out + 10 );
}

void t_string_1_1_10(){
	puts("|");
	char out[21];
	char * out_next_byte = NULL;
	char * expected = "4294967296";
	uint64 i = 4294967296ULL;
	BOOL is_unsigned = TRUE;
	out_next_byte = i64toa( out , i , is_unsigned );
	//puts("out=!"); puts(out); putc('!');
	//puts("expected=!"); puts(expected); putc('!');
	assert( strcmp(out,expected) == 0 );
	assert( out_next_byte == out + 10 );
}

void t_string(){
	puts("<t_string>");
	t_string_1_1_1();
	t_string_1_1_2();
	t_string_1_1_3();
	t_string_1_1_4();
	//t_string_1_1_5();
	t_string_1_1_6();
	t_string_1_1_7();
	t_string_1_1_8();
	t_string_1_1_9();
	//t_string_1_1_10();
}
