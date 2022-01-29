#ifndef _RECORD_CONTROL_H_
#define _RECORD_CONTROL_H_

#include "HT66F018.h"

/*#define RECORD_IO	_pb3	*/

#define gpio_set(X,Z)	X = Z	

void set_voice(unsigned char date_v);
void use_delay_us(unsigned int us_s);

extern volatile unsigned char user_delay_flag;
extern volatile unsigned int user_delay_time;


#endif
