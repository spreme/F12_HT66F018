#ifndef __MENU_H__
#define __MENU_H__



char set_val(char dat,char min,char max,u8 addr);

char set_time(void);

char set_meal(void);

void get_meal(u8 num);

extern u8 set_time_flag;
extern u8 set_meal_flag;

#endif
