#ifndef __CLOCK_RUN_H__
#define __CLOCK_RUN_H__

void rtc_init(void);

void Clock_Run();

void time_save();			//����ʱ��

struct rtc_time {
	volatile uchar hour;
	volatile uchar minute;
	volatile uchar second;
};

extern struct rtc_time rtc_date;

//extern volatile int lcd_timeout;		//��ʱ


#endif