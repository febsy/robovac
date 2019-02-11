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
#include "vacuum.h"
#include "drivesystem.h"
#include "tracker.h"

#include "globals.h"

#define LEDPORT PORTC
#define LEDRED 0b00000100
#define LEDGREEN 0b00001000

int16_t mT1;
volatile uint8_t mStatusFlag;

uint8_t config_init()
{
	mStatusFlag = 'A'; // initialize to "low Battery flag"
	DDRC |= 0b00001100; // init LED's
	return 1;
}

uint8_t config_setLED(uint8_t led,uint8_t state,uint8_t sync)
{
	if (state == 1)
	{
		PORTC |= led;
	}
	else if (state == 0)
	{
		PORTC &= ~led;
	}
	else if (state == 2)
	{
		PORTC = (((led&PORTC)^led)|(PORTC&~led));
	}
	else if (state == 3)
	{
		if ((sync & PORTC)==sync)
		{
			PORTC |= led;
		}
		else
		{
			PORTC &= ~led;
		}
	}
	else
	{
		return 0;
	}
	return 1;
}

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

	return (uint16_t)(mSysTimeMs/1000);
}

uint8_t config_NTP(uint8_t phase,int16_t t2,int16_t t3) // phase 0 - save T1, phase 1 get T2 & T3 save T4 and calculate TIME = ((T2-T1)+(T3-T4))/2 -> return TIME
{
	if (phase == 0)
	{
		mT1 = (int16_t)(mSysTimeMs/1000);
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
	drivesystem_isReady();	// PRIORITY 4
	//STUCK					// PRIORITY 3
	tracker_isInitialized();// PRIORITY 2
	bms_getBatteryLoad();	// PRIORITY 1&0
	if(mStatusFlag != 'R')
	{
		switch (mStatusFlag)
		{
		case 'S':
			config_setLED(LEDGREEN,0,0);
			config_setLED(LEDRED,2,0);
			drivesystem_Stop();
			mDriveSystemReady = 0;
			break;
		case 'C':
			config_setLED(LEDGREEN,1,0);
			config_setLED(LEDRED,2,0);
			break;
		case 'L':
			config_setLED(LEDGREEN,1,0);
			config_setLED(LEDRED,1,0);
		case 'A':
			config_setLED(LEDGREEN,0,0);
			config_setLED(LEDRED,1,0);
			vacuum_setState(0);
			break;
		default:
			return 0;
			break;
		}
	}
	else
	{
		config_setLED(LEDGREEN,1,0);
		config_setLED(LEDRED,0,0);
	}
	return 1;
}
