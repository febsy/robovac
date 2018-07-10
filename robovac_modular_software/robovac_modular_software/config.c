/*
 * config.c
 *
 * Created: 11.06.2018 23:02:11
 *  Author: feb
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

#include "system_time.h"
#include "bms.h"

#include "globals.h"

unsigned long mT1;
volatile uint8_t mStatusFlag;

uint8_t config_getStatus()
{
	return mStatusFlag;
}

uint8_t config_getBatteryStatus()
{
	return bms_getBatteryLoad();
}

uint16_t config_getTime()
{

	return (int16_t)(mSysTimeMs/1000);
}

uint8_t config_NTP(uint8_t phase,int16_t t2,int16_t t3) // phase 0 - save T1, phase 1 get T2 & T3 save T4 and calculate TIME = ((T2-T1)+(T3-T4))/2 -> return TIME
{
	if (phase == 0)
	{
		mT1 = mSysTimeMs;
		return 0;
	}
	else if (phase == 1)
	{
		int delay = 0;
		system_time_SetTime(mT1,t2,t3,(int16_t)(mSysTimeMs/1000),&delay);
		return delay;
	}
	return -1;
}

uint8_t config_flagDEAMON()
{
	drivesystem_isReady();	// PRIORITY 3
	//STUCK					// PRIORITY 2
	//CORR					// PRIORITY 1
	bms_getBatteryLoad();	// PRIORITY 0
	return 1;
}
