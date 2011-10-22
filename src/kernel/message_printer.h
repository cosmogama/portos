#ifndef _MESSAGE_PRINTER_H
#define _MESSAGE_PRINTER_H

void turn_off_error_msgs();
void turn_off_warning_msgs();
void turn_on_error_msgs();
void turn_on_warning_msgs();

void error_msg(const char * format , ... );
void warning_msg(const char * format , ... );

#endif
