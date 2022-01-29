#ifndef	_TM1628_H
#define	_TM1628_H

#include "init_ht66f018.h"


void send_8bit(uchar dat);

void send_command(uchar com);

void Write_DATA(uchar add,uchar DATA);

void init_TM1628(void);


#endif
