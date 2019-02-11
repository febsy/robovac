/*
 * tracker.c
 *
 * Created: 11.06.2018 23:01:11
 *  Author: feb
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <math.h>

#include "tracker.h"
#include "ultrasonic.h"
#include "hmc5843.h"
#include "globals.h"

int16_t mDistancePerUnit = 1;
int16_t mAnglePerUnit = 1;
volatile int16_t mCurrentPosX = 0;
volatile int16_t mCurrentPosY = 0;
volatile int16_t mCurrentAngle = 0;
volatile unsigned long mPositionTime = 0;

uint8_t tracker_init()
{
	mDistancePerUnit = 0;
	mAnglePerUnit = 0;
	return 1;
}

uint8_t tracker_isInitialized()
{
	if (mDistancePerUnit == 0 || mAnglePerUnit == 0)
	{
		mStatusFlag = 'C';
	}
	return 1;
}

uint8_t tracker_getPosition(uint8_t objmode,int16_t* x,int16_t* y,int16_t* a_h) // ObjectMode A: Return X,Y,Angle ; ObjectMode O: Return X,Y,Bool
{
	*x = mCurrentPosX;
	*y = mCurrentPosY;
	if (objmode == 'O')
	{
		int16_t us1=400;
		int16_t us2=400;
		tracker_getUSDistance(&us1,&us2);
		if(us1 < 15 || us2 < 15)
		{
			*a_h = 1;
		}
		else
		{
			*a_h = 0;
		}
	}
	else
	{
		*a_h = mCurrentAngle;
	}
	return 0;
}

uint8_t tracker_getUSDistance(int16_t* us1,int16_t* us2)
{
	return ultrasonic_getDistance(us1,us2);
}

uint8_t tracker_getAngle(int16_t* angle)
{
	hmc5883_mean_angle();
	*angle = mCurrentAngle;
	return 1;
}

uint8_t tracker_setHome(int16_t x,int16_t y)
{
	mCurrentPosX = x;
	mCurrentPosY = y;
	return 1;
}

uint8_t tracker_setOrientation(int16_t a)
{
	mCurrentAngle = a;
	return 1;
}

uint8_t tracker_setDistancePerUnit(int16_t dpu)
{
	mDistancePerUnit = dpu;
	return 1;
}

uint8_t tracker_setAnglePerUnit(int16_t apu)
{
	mAnglePerUnit = apu;
	return 1;
}

uint8_t tracker_refreshPositionDEAMON(void)
{
	
	if (mDSDStatus > 0)
	{
		mCurrentPosX += ((mSysTimeMs - mPositionTime)*mDistancePerUnit) * cos(0.0175*mCurrentAngle);
		mCurrentPosY += ((mSysTimeMs - mPositionTime)*mDistancePerUnit) * sin(0.0175*mCurrentAngle);
	}
	mPositionTime = mSysTimeMs;
	return 1;
}
