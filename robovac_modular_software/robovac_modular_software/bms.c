/*
 * bms.c
 *
 * Created: 24.04.2018 22:11:15
 *  Author: feb
 */ 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>

#include "adc.h"
#include "bms.h"

#include "globals.h"

#define FULLBATTERY 7811.1

volatile uint8_t mBatteryLoad = 124;

uint8_t bms_init(void)
{
	adc_init();
	return 1;
}

uint8_t bms_getBatteryLoad(void)
{
	float batload = ((adc_getvalue()*1000.00)/FULLBATTERY);
	mBatteryLoad = (uint8_t)batload;
	if (mBatteryLoad < 50)
	{
		mStatusFlag = 'L';
	}
	if (mBatteryLoad < 30)
	{
		mStatusFlag = 'A';
	}
	return mBatteryLoad;
}