#ifndef __KEYSCAN_H__
#define __KEYSCAN_H__

#include "define.h"

u8 key_scan(void);

void key_func(void);

extern u8 key_flag;
extern u16 g_nConversionValue;

#endif