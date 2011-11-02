#include "printf.h"
#include "types.h"

BOOL print_error_msgs = TRUE;
BOOL print_warning_msgs = TRUE;
BOOL print_info_msgs = TRUE;
BOOL print_debug_msgs = TRUE;

void turn_off_error_msgs(){
	print_error_msgs = FALSE;
}

void turn_off_warning_msgs(){
	print_warning_msgs = FALSE;
}

void turn_off_info_msgs(){
	print_info_msgs = FALSE;
}

void turn_off_debug_msgs(){
	print_debug_msgs = FALSE;
}

void turn_on_error_msgs(){
	print_error_msgs = TRUE;
}

void turn_on_warning_msgs(){
	print_warning_msgs = TRUE;
}

void turn_on_info_msgs(){
	print_info_msgs = TRUE;
}

void turn_on_debug_msgs(){
	print_debug_msgs = TRUE;
}

void error_msg(const char * format , ... ){
	int *varg = (int *)(&format);
	if( print_error_msgs ) print( NULL , varg );
}

void warning_msg(const char * format , ... ){
	int *varg = (int *)(&format);
	if( print_warning_msgs ) print( NULL , varg );
}

void info_msg(const char * format , ... ){
	int *varg = (int *)(&format);
	if( print_info_msgs ) print( NULL , varg );
}

void debug_msg(const char * format , ... ){
	int *varg = (int *)(&format);
	if( print_debug_msgs ) print( NULL , varg );
}

