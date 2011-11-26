#include "tests.h"
#include "test_sanity.h"
#include "t_string.h"
#include "t_printf.h"
#include "t_print_arg.h"
#include "t_printf2.h"
#include "t_kmalloc_kfree_util.h"
#include "t_kmalloc_kfree_sanity.h"
#include "t_IDE.h"

#include "message_printer.h"

void run_tests(void){

  // turn off all messages so that we only see test results
	turn_off_error_msgs();
	turn_off_warning_msgs();
	turn_off_info_msgs();
	turn_off_debug_msgs();

	// run tests
	t_string();
	t_print_arg();
	t_printf();
	t_printf2();
	t_kmalloc_kfree_util();
	t_kmalloc_kfree_sanity();
	// t_IDE();

  // turn messages back on
	turn_on_error_msgs();
	//turn_on_warning_msgs();
	//turn_on_info_msgs();
	//turn_on_debug_msgs();
}

