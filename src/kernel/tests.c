#include "test_sanity.h"
#include "t_kmalloc_kfree_util.h"
#include "t_kmalloc_kfree_sanity.h"
#include "message_printer.h"

void run_tests(){
	turn_off_error_msgs();
	turn_off_warning_msgs();
	//t_kmalloc_kfree_util();
	t_kmalloc_kfree_sanity();
	turn_on_error_msgs();
	turn_on_warning_msgs();
}
