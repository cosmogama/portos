#if RUN_TESTS == true

#include "tests.h"
#include "test_sanity.h"
#include "t_string.h"
#include "t_printf.h"
#include "t_kmalloc_kfree.h"
#include "message_printer.h"

void run_tests(void){
	turn_off_error_msgs();
	turn_off_warning_msgs();
	turn_off_info_msgs();
	turn_off_debug_msgs();
	t_string();
	t_print_arg();
	t_printf();
	t_printf2();
	t_kmalloc_kfree_util();
	t_kmalloc_kfree_sanity();
	turn_on_error_msgs();
	//turn_on_warning_msgs();
	//turn_on_info_msgs();
	//turn_on_debug_msgs();
}

#endif
