/*
 * system_time.c
 *
 * Created: 08.04.2018 16:48:32
 *  Author: feb
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>

#include "system_time.h"
#include "globals.h"


volatile uint64_t mSysTimeMs = 0;
volatile uint16_t mTimeprescaler = 0;
uint8_t mSysTimeAdjustment = 96;	// 100 ms

uint8_t system_time_init(void)
{
	mSysTimeAdjustment = 96;
	mSysTimeMs = 0;
	return 1;
} 

void system_time_IRQDeamon(void)
{
	mTimeprescaler++;
	if (mTimeprescaler == 1000)
	{
		mTimeprescaler = 0;
		mSysTimeMs += mSysTimeAdjustment;
	}
}

int16_t system_time_SetTime(int16_t t0, int16_t t1, int16_t t2, int16_t t3,int16_t *delay)
{
	*delay = (t3 - t0) - (t2 - t1);
	long intern_t1 = t0;
	long intern_t2 = t1;
	long intern_t3 = t2;
	long intern_t4 = t3;
	mSysTimeMs += (long)((((intern_t2 - intern_t1) + (intern_t3 - intern_t4))/2) * 1000);
	return (mSysTimeMs/1000);
}

unsigned long system_time_GetUs(void){
	unsigned long ustime = (mTimeprescaler+1) * 100 + (50 * TCNT0); // mTimeprescaler * 100 = us + register * 50 = us --> Overflow nach 1 ms
	return ustime;
}