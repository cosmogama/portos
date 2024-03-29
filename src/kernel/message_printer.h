#ifndef _MESSAGE_PRINTER_H
#define _MESSAGE_PRINTER_H

void turn_off_error_msgs(void);
void turn_off_warning_msgs(void);
void turn_off_info_msgs(void);
void turn_off_debug_msgs(void);
void turn_on_error_msgs(void);
void turn_on_warning_msgs(void);
void turn_on_info_msgs(void);
void turn_on_debug_msgs(void);

void error_msg(const char * format , ... );
void warning_msg(const char * format , ... );
void info_msg(const char * format , ... );
void debug_msg(const char * format , ... );

#endif
