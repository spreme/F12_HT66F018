#ifndef __FEED_H__
#define __FEED_H__

#define FEED_MAX_NUM 6 //��ʱιʳ�������

struct feed_record {
	u8 hour;
	u8 minute;
	u8 quantity;		//ιʳ��
	u8 music;
};


extern u8 feed_run(struct feed_record *info);

extern void feed_scan(struct feed_record *feed);

extern u8 feed_going;

extern struct feed_record feed_plans[FEED_MAX_NUM];

#endif