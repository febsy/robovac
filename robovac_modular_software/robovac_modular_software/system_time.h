/*
 * system_time.h
 *
 * Created: 24.04.2018 20:39:55
 *  Author: feb
 */ 


#ifndef SYSTEM_TIME_H_
#define SYSTEM_TIME_H_

extern volatile unsigned long mSysTimeMs;
extern uint8_t mSysTimeAdjustment;

uint8_t system_time_init(void);

void system_time_IRQDeamon(void);
unsigned long system_time_GetUs(void);
int16_t system_time_SetTime(int16_t, int16_t, int16_t, int16_t,int16_t*);

#endif /* SYSTEM_TIME_H_ */