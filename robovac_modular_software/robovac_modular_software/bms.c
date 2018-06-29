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

#define FULLBATTERY 1000

uint8_t mBatteryLoad = 124;

uint8_t bms_init(void)
{
	adc_init();
	return 1;
}

uint8_t bms_getBatteryLoad(void)
{
	uint16_t batload = (adc_getvalue()*100)/FULLBATTERY;
	mBatteryLoad = (uint8_t)batload;
	return (uint8_t)batload;
}