#include "message_printer.h"
#include "printf.h"
#include "monitor.h"
#include "assert.h"
#include "string.h"

void t_printf_1_0_1(void){
	puts("|1.0.*|");

	// arg format
	char format_specifier = VA_BYTE;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[5];
	char * bptr = &buff[0];
	// arg to process
	BYTE b = 103;
	// assemble varg
	int * varg = (int *)&b;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '1' && buff[1] == '0' && buff[2] == '3' && buff[3] == '\0' );
}

void t_printf_1_0_2(void){
	puts("|");

	// arg format
	char format_specifier = VA_BYTE;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[5];
	char * bptr = &buff[0];
	// arg to process
	BYTE b = -103;
	// assemble varg
	int * varg = (int *)&b;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '-' && buff[1] == '1' && buff[2] == '0' && buff[3] == '3' && buff[4] == '\0' );
}

void t_printf_1_0_3(void){
	puts("|");

	// arg format
	char format_specifier = VA_BYTE;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[5];
	char * bptr = &buff[0];
	// arg to process
	BYTE b = 255;
	// assemble varg
	int * varg = (int *)&b;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '-' && buff[1] == '1' && buff[4] == '\0' );
}

void t_printf_1_1_1(void){
	puts("|1.1.*|");

	// arg format
	char format_specifier = VA_CHAR;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[2];
	char * bptr = &buff[0];
	// char to process
	char c = 't';
	// assemble varg
	int * varg = (int *)&c;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == c && buff[1] == '\0' );
}

void t_printf_1_1_2(void){
	puts("|");

	// arg format
	char format_specifier = VA_CHAR;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[2];
	char * bptr = &buff[0];
	// char to process
	char c = '\0';
	// assemble varg
	int * varg = (int *)&c;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == c && buff[1] == '\0' );
}

void t_printf_1_1_3(void){
	puts("|");

	// arg format
	char format_specifier = VA_CHAR;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[2];
	char * bptr = &buff[0];
	// char to process
	char c = '\n';
	// assemble varg
	int * varg = (int *)&c;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == c && buff[1] == '\0' );
}

void t_printf_1_2_1(void){
	puts("|1.2.*|");

	// arg format
	char format_specifier = VA_SHORT;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// int to process
	short arg = 0;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	//puts("expected="); puts(expected); putc(' ');
	assert(buff[0]=='0' && buff[1]=='\0');
}

void t_printf_1_2_2(void){
	puts("|");

	// arg format
	char format_specifier = VA_SHORT;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// int to process
	short arg = -54;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert(buff[0]=='-' && buff[1]=='5' && buff[2]=='4' && buff[3]=='\0');
}

void t_printf_1_2_3(void){
	puts("|");

	// arg format
	char format_specifier = VA_SHORT;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// int to process
	short arg = 32767;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert(buff[0]=='3' && buff[1]=='2' && buff[2]=='7' && buff[3]=='6' && buff[4]=='7' && buff[5]=='\0');
}

void t_printf_1_3_1(void){
	puts("|1.3.*|");

	// arg format
	char format_specifier = VA_INT;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// int to process
	int arg = 1234;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert(buff[0]=='1' && buff[1]=='2' && buff[2]=='3' && buff[3]=='4' && buff[4]=='\0');
}

void t_printf_1_3_2(void){
	puts("|");

	// arg format
	char format_specifier = VA_INT;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// int to process
	int arg = -234;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert(buff[0]=='-' && buff[1]=='2' && buff[2]=='3' && buff[3]=='4' && buff[4]=='\0');
}

void t_printf_1_3_3(void){
	puts("|");

	// arg format
	char format_specifier = VA_INT;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// int to process
	int arg = 2147483647;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert(buff[0]=='2' && buff[1]=='1' && buff[2]=='4' && buff[3]=='7' && buff[4]=='4' &&
		buff[5]=='8' && buff[6]=='3' && buff[7]=='6' && buff[8]=='4' && buff[9]=='7' && buff[10]=='\0');
}

void t_printf_1_4_1(void){
	puts("|1.4.*|");

	// arg format
	char format_specifier = VA_LONG;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// int to process
	long arg = 1234;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert(buff[0]=='1' && buff[1]=='2' && buff[2]=='3' && buff[3]=='4' && buff[4]=='\0');
}

void t_printf_1_4_2(void){
	puts("|");

	// arg format
	char format_specifier = VA_LONG;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// arg to process
	long arg = -234;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert(buff[0]=='-' && buff[1]=='2' && buff[2]=='3' && buff[3]=='4' && buff[4]=='\0');
}

void t_printf_1_4_3(void){
	puts("|");

	// arg format	
	char format_specifier = VA_LONG;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// arg to process
	long arg = 2147483647;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert(buff[0]=='2' && buff[1]=='1' && buff[2]=='4' && buff[3]=='7' && buff[4]=='4' &&
		buff[5]=='8' && buff[6]=='3' && buff[7]=='6' && buff[8]=='4' && buff[9]=='7' && buff[10]=='\0');
}

void t_printf_1_5_1(void){
	puts("|1.5.*|");

	// arg format	
	char format_specifier = VA_FLOAT;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// arg to process
	float arg = 1234.5678;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert(buff[0]=='1' && buff[1]=='2' && buff[2]=='3' && buff[3]=='4' && buff[4]=='.' &&
		buff[5]=='5' && buff[6]=='6' && buff[7]=='7' && buff[8]=='8' && buff[10]=='\0');
}

void t_printf_1_5_2(void){
	puts("|");

	// arg format	
	char format_specifier = VA_FLOAT;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// arg to process
	float arg = -234.5678;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert(buff[0]=='-' && buff[1]=='2' && buff[2]=='3' && buff[3]=='4' && buff[4]=='.' &&
		buff[5]=='5' && buff[6]=='6' && buff[7]=='7' && buff[8]=='8' && buff[10]=='\0');
}

void t_printf_1_6_1(void){
	puts("|1.6.*|");

	// arg format	
	char format_specifier = VA_DOUBLE;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[21];
	char * bptr = &buff[0];
	// arg to process
	double arg = 123123123123123.5678;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert(buff[0]=='1' && buff[1]=='2' && buff[2]=='3' 
		&& buff[3]=='1' && buff[4]=='2' && buff[5]=='3' 
		&& buff[6]=='1' && buff[7]=='2' && buff[8]=='3' 
		&& buff[9]=='1' && buff[10]=='2' && buff[11]=='3'
		&& buff[12]=='1' && buff[13]=='2' && buff[14]=='3'
		&& buff[15]=='.' && buff[16]=='5' && buff[17]=='6' && buff[18]=='7' && buff[19]=='8'
		&& buff[20]=='\0'
	);
}

void t_printf_1_6_2(void){
	puts("|");

	// arg format	
	char format_specifier = VA_DOUBLE;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[21];
	char * bptr = &buff[0];
	// arg to process
	double arg = -23123123123123.5678;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert(buff[0]=='-' && buff[1]=='2' && buff[2]=='3' 
		&& buff[3]=='1' && buff[4]=='2' && buff[5]=='3' 
		&& buff[6]=='1' && buff[7]=='2' && buff[8]=='3' 
		&& buff[9]=='1' && buff[10]=='2' && buff[11]=='3'
		&& buff[12]=='1' && buff[13]=='2' && buff[14]=='3'
		&& buff[15]=='.' && buff[16]=='5' && buff[17]=='6' && buff[18]=='7' && buff[19]=='8'
		&& buff[20]=='\0'
	);
}

void t_printf_1_7_1(void){
	puts("|1.7.*|");

	// arg format	
	char format_specifier = VA_INT64;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[21];
	char * bptr = &buff[0];
	// arg to process
	int64 arg = 123123123123123LL;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert(buff[0]=='1' && buff[1]=='2' && buff[2]=='3' 
		&& buff[3]=='1' && buff[4]=='2' && buff[5]=='3' 
		&& buff[6]=='1' && buff[7]=='2' && buff[8]=='3' 
		&& buff[9]=='1' && buff[10]=='2' && buff[11]=='3'
		&& buff[12]=='1' && buff[13]=='2' && buff[14]=='3'
		&& buff[15]=='\0'
	);
}

void t_printf_1_7_2(void){
	puts("|");

	// arg format	
	char format_specifier = VA_INT64;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[21];
	char * bptr = &buff[0];
	// arg to process
	int64 arg = -23123123123123LL;
	// assemble varg
	int * varg = (int *)&arg;
	
	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert(buff[0]=='-' && buff[1]=='2' && buff[2]=='3' 
		&& buff[3]=='1' && buff[4]=='2' && buff[5]=='3' 
		&& buff[6]=='1' && buff[7]=='2' && buff[8]=='3' 
		&& buff[9]=='1' && buff[10]=='2' && buff[11]=='3'
		&& buff[12]=='1' && buff[13]=='2' && buff[14]=='3'
		&& buff[15]=='\0'
	);
}

void t_printf_1_8_1(void){
	puts("|1.8.*|");

	// arg format
	char format_specifier = VA_BYTE;
	BOOL is_unsigned = TRUE;
	// buffer to capture output of function
	char buff[5];
	char * bptr = &buff[0];
	// arg to process
	UBYTE b = 103;
	// assemble varg
	int * varg = (int *)&b;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '1' && buff[1] == '0' && buff[2] == '3' && buff[3] == '\0' );
}

void t_printf_1_8_2(void){
	puts("|");

	// arg format
	char format_specifier = VA_BYTE;
	BOOL is_unsigned = TRUE;
	// buffer to capture output of function
	char buff[5];
	char * bptr = &buff[0];
	// arg to process
	UBYTE b = 255;
	// assemble varg
	int * varg = (int *)&b;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '2' && buff[1] == '5' && buff[2] == '5' && buff[3] == '\0' );
}

void t_printf_1_9_1(void){
	puts("|1.9.*|");

	// arg format
	char format_specifier = VA_SHORT;
	BOOL is_unsigned = TRUE;
	// buffer to capture output of function
	char buff[6];
	char * bptr = &buff[0];
	// arg to process
	uint16 us = 103;
	// assemble varg
	int * varg = (int *)&us;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '1' && buff[1] == '0' && buff[2] == '3' && buff[3] == '\0' );
}

void t_printf_1_9_2(void){
	puts("|");

	// arg format
	char format_specifier = VA_SHORT;
	BOOL is_unsigned = TRUE;
	// buffer to capture output of function
	char buff[6];
	char * bptr = &buff[0];
	// arg to process
	uint16 us = 65535;
	// assemble varg
	int * varg = (int *)&us;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '6' && buff[1] == '5' && buff[2] == '5' && buff[3] == '3' && buff[4] == '5' && buff[5] == '\0' );
}

void t_printf_1_10_1(void){
	puts("|1.10.*|");

	// arg format
	char format_specifier = VA_INT;
	BOOL is_unsigned = TRUE;
	// buffer to capture output of function
	char buff[11];
	char * bptr = &buff[0];
	// arg to process
	uint32 ui = 103;
	// assemble varg
	int * varg = (int *)&ui;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '1' && buff[1] == '0' && buff[2] == '3' && buff[3] == '\0' );
}

void t_printf_1_10_2(void){
	puts("|");

	// arg format
	char format_specifier = VA_INT;
	BOOL is_unsigned = TRUE;
	// buffer to capture output of function
	char buff[11];
	char * bptr = &buff[0];
	// arg to process
	uint32 ui = 4294967295U;
	// assemble varg
	int * varg = (int *)&ui;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '4' && buff[1] == '2' && buff[2] == '9' && buff[3] == '4' && buff[4] == '9' && buff[5] == '6' 
		&& buff[6] == '7' && buff[7] == '2' && buff[8] == '9' && buff[9] == '5' && buff[10] == '\0' );
}

void t_printf_1_11_1(void){
	puts("|1.11.*|");

	// arg format
	char format_specifier = VA_LONG;
	BOOL is_unsigned = TRUE;
	// buffer to capture output of function
	char buff[11];
	char * bptr = &buff[0];
	// arg to process
	unsigned long ul = 103;
	// assemble varg
	int * varg = (int *)&ul;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '1' && buff[1] == '0' && buff[2] == '3' && buff[3] == '\0' );
}

void t_printf_1_11_2(void){
	puts("|");

	// arg format
	char format_specifier = VA_LONG;
	BOOL is_unsigned = TRUE;
	// buffer to capture output of function
	char buff[11];
	char * bptr = &buff[0];
	// arg to process
	unsigned long ul = 4294967295LU;
	// assemble varg
	int * varg = (int *)&ul;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '4' && buff[1] == '2' && buff[2] == '9' && buff[3] == '4' && buff[4] == '9' && buff[5] == '6' 
		&& buff[6] == '7' && buff[7] == '2' && buff[8] == '9' && buff[9] == '5' && buff[10] == '\0' );
}

void t_printf_1_12_1(void){
	puts("|1.12.*|");

	// arg format
	char format_specifier = VA_INT64;
	BOOL is_unsigned = TRUE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// arg to process
	uint64 ui = 4294967295LLU;
	// assemble varg
	int * varg = (int *)&ui;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '4' && buff[1] == '2' && buff[2] == '9' && buff[3] == '4' && buff[4] == '9' && buff[5] == '6' 
		&& buff[6] == '7' && buff[7] == '2' && buff[8] == '9' && buff[9] == '5' && buff[10] == '\0' );
}

void t_printf_1_12_2(void){
	puts("|");

	// arg format
	char format_specifier = VA_INT64;
	BOOL is_unsigned = TRUE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// arg to process
	uint64 ui = 4294967296LLU;
	// assemble varg
	int * varg = (int *)&ui;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '4' && buff[1] == '2' && buff[2] == '9' && buff[3] == '4' && buff[4] == '9' && buff[5] == '6' 
		&& buff[6] == '7' && buff[7] == '2' && buff[8] == '9' && buff[9] == '6' && buff[10] == '\0' );
}

void t_printf_1_13_1(void){
	puts("|1.13.*|");

	// arg format
	char format_specifier = VA_HEX;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// arg to process
	uint32 ui = 571920;
	// assemble varg
	int * varg = (int *)&ui;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	// puts("hex1="); puts(bptr); putc(' ');
	assert( buff[0] == '0' && buff[1] == 'x' && buff[2] == '0' && buff[3] == '0' &&
		buff[4] == '0' && buff[5] == '8' && buff[6] == 'B' && 
		buff[7] == 'A' && buff[8] == '1' && buff[9] == '0' && buff[10] == '\0'); 
}

void t_printf_1_13_2(void){
	puts("|");

	// arg format
	char format_specifier = VA_HEX;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// arg to process
	uint32 ui = 4294967295U;
	// assemble varg
	int * varg = (int *)&ui;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	// puts("hex2="); puts(bptr); putc(' ');
	assert( buff[0] == '0' && buff[1] == 'x' && buff[2] == 'F' && buff[3] == 'F' && buff[4] == 'F' && buff[5] == 'F' 
		&& buff[6] == 'F' && buff[7] == 'F' && buff[8] == 'F' && buff[9] == 'F' && buff[10] == '\0' );
}

void t_printf_1_14_1(void){
	puts("|1.14.*|");

	// arg format
	char format_specifier = VA_STRING;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// arg to process
	const char * str = NULL;
	// assemble varg
	int * varg = (int *)&str;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '(' && buff[1] == 'n' && buff[2] == 'u' && buff[3] == 'l' && buff[4] == 'l' && buff[5] == ')' 
		&& buff[6] == '\0' );
}

void t_printf_1_14_2(void){
	puts("|");

	// arg format
	char format_specifier = VA_STRING;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// arg to process
	const char * str = "";
	// assemble varg
	int * varg = (int *)&str;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '\0' );
}

void t_printf_1_14_3(void){
	puts("|");

	// arg format
	char format_specifier = VA_STRING;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// arg to process
	const char * str = "I'm a str.";
	// assemble varg
	int * varg = (int *)&str;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == 'I' && buff[1] == '\'' && buff[2] == 'm' && buff[3] == ' ' && buff[4] == 'a' && buff[5] == ' ' 
		&& buff[6] == 's' && buff[7] == 't' && buff[8] == 'r' && buff[9] == '.' && buff[10] == '\0' );
}

void t_printf_1_14_4(void){
	puts("|");

	// arg format
	char format_specifier = VA_STRING;
	BOOL is_unsigned = FALSE;
	// buffer to capture output of function
	char buff[20];
	char * bptr = &buff[0];
	// arg to process
	const char * str = "!@#$%^&*<>";
	// assemble varg
	int * varg = (int *)&str;

	print_arg(&bptr , is_unsigned , format_specifier , varg);
	assert( buff[0] == '!' && buff[1] == '@' && buff[2] == '#' && buff[3] == '$' && buff[4] == '%' && buff[5] == '^' 
		&& buff[6] == '&' && buff[7] == '*' && buff[8] == '<' && buff[9] == '>' && buff[10] == '\0' );
}

void t_print_arg(void){
	puts("<print_arg>");
	t_printf_1_0_1();
	t_printf_1_0_2();
	t_printf_1_0_3();
	t_printf_1_1_1();
	t_printf_1_1_2();
	t_printf_1_1_3();
	t_printf_1_2_1();
	t_printf_1_2_2();
	t_printf_1_2_3();
	t_printf_1_3_1();
	t_printf_1_3_2();
	t_printf_1_3_3();
	t_printf_1_4_1();
	t_printf_1_4_2();
	t_printf_1_4_3();
	//t_printf_1_5_1();
	//t_printf_1_5_2();
	//t_printf_1_6_1();
	//t_printf_1_6_2();
	//t_printf_1_7_1();
	//t_printf_1_7_2();
	t_printf_1_8_1();
	t_printf_1_8_2();
	t_printf_1_9_1();
	t_printf_1_9_2();
	t_printf_1_10_1();
	t_printf_1_10_2();
	t_printf_1_11_1();
	t_printf_1_11_2();
	t_printf_1_12_1();
	t_printf_1_12_2();
	t_printf_1_13_1();
	t_printf_1_13_2();
	t_printf_1_14_1();
	t_printf_1_14_2();
	t_printf_1_14_3();
	t_printf_1_14_4();
}

