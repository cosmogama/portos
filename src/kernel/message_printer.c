#include "printf.h"

BOOL print_errors = TRUE;
BOOL print_warnings = TRUE;

void turn_off_error_msgs(){
	print_errors = FALSE;
}

void turn_off_warning_msgs(){
	print_warnings = FALSE;
}

void turn_on_error_msgs(){
	print_errors = TRUE;
}

void turn_on_warning_msgs(){
	print_warnings = TRUE;
}

void ErrorMsg(const char * format , ... ){
	if( print_errors ) printf(format,NULL);
}

void WarningMsg(const char * format , ... ){
	if( print_warnings ) printf(format,NULL);
}
