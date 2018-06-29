/*
 * config.c
 *
 * Created: 11.06.2018 23:02:11
 *  Author: feb
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

#include "globals.h"

unsigned long mT1;

uint8_t config_getStatus()
{

	return 0;
}

uint8_t config_getBatteryStatus()
{

	return 0;
}

uint16_t config_getTime()
{

	return 0;
}

uint8_t config_NTP(uint8_t phase,int16_t t2,int16_t t3) // phase 0 - save T1, phase 1 get T2 & T3 save T4 and calculate TIME = ((T2-T1)+(T3-T4))/2 -> return TIME
{
	if (phase == 0)
	{
		mT1 = mSysTimeMs;
		return (int)(mSysTimeMs/1000);;
	}
	else if (phase == 1)
	{
		mSysTimeMs = ((((t2 * 1000)-mT1)+((t3 * 1000)- mSysTimeMs))/2);
		return (int)(mSysTimeMs/1000);;
	}
	return -1;
}
