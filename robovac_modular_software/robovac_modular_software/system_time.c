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


volatile unsigned long mSysTimeMs = 0;
uint8_t mSysTimeAdjustment = 100;	// 100 ms

uint8_t system_time_init(void)
{
	mSysTimeAdjustment = 100;
	mSysTimeMs = 0;
	return 1;
} 

void system_time_IRQDeamon(void)
{
	mSysTimeMs += mSysTimeAdjustment;
}

int16_t system_time_SetTime(int16_t t0, int16_t t1, int16_t t2, int16_t t3,int16_t *delay)
{
	*delay = (t3 - t0) - (t2 - t1);
	mSysTimeMs += (long)((((t1 - t0) + (t2 - t3))/2) * 1000);
	return (mSysTimeMs/1000);
}