/*
 * drivesystem.c
 *
 * Created: 11.06.2018 21:39:39
 *  Author: feb
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <math.h>

#include "globals.h"
#include "drivesystem.h"

uint8_t mDriveSystemReady = 0;
volatile unsigned long mTravelTime = 0;
volatile unsigned long mAngleTravelTime = 0;

volatile int8_t mAngleDirection = -1;
volatile uint8_t mDSDStatus = 0b00000000;
volatile uint8_t mDSDLinear = 0;
volatile uint8_t mDSDAngle = 0;
volatile unsigned long mDSDTargetTime = 0;

uint8_t drivesystem_init()
{
	mTravelTime = 0;
	mAngleTravelTime = 0;
	mAngleDirection = -1;
	mDSDStatus = 0b00000000;
	mDSDLinear = 0;
	mDSDAngle = 0;
	mDSDTargetTime = 0;
	DDRD |= 0b11100000;
	DDRB |= 0b00000111;
	PORTD |= 0b01100000;
	mDriveSystemReady = 1;
	return 1;
}

uint8_t drivesystem_isReady(void)
{
	return mDriveSystemReady;
}

uint8_t drivesystem_SetDestination(int16_t x,int16_t y)
{
	if (mDSDStatus == 0)
	{
		mDSDLinear = 0;
		mDSDAngle = 0;
		int16_t rel_pos_x = x - mCurrentPosX;
		int16_t rel_pos_y = y - mCurrentPosY;
		int16_t dest_angle = atan2(rel_pos_y,rel_pos_x);
		int16_t dest_dist = (int16_t)sqrt((pow((double)rel_pos_x,2)+pow((double)rel_pos_y,2)));
		int8_t dest_dir = 0;
		if (dest_angle - mCurrentAngle > 0)
		{
			dest_dir = 1;
		}
		else if (dest_angle - mCurrentAngle < 0)
		{
			dest_dir = -1;
		}
		if(dest_dir != 0)
		{
			drivesystem_SetAngle(dest_dir,dest_angle);
		}
		if (dest_dist > 0)
		{
			drivesystem_SetDistance(dest_dist);
		}
		return 1;
	}
	return 0;
}

uint8_t drivesystem_SetDistance(int16_t dist)
{
	mTravelTime = ((unsigned long)dist * 1000 / mDistancePerUnit);
	mDSDStatus |= 1;
	return 1;
}

uint8_t drivesystem_SetAngle(int8_t dir,uint16_t a)
{
	mAngleDirection = dir;
	mAngleTravelTime = ((unsigned long)a * 1000 / mAnglePerUnit);
	mDSDStatus |= 2;
	return 1;
}

uint8_t drivesystem_Stop(void)
{
	PORTD |= (0b10000000);
	PORTB |= (0b00000001);
	PORTB |= (0b00000110);
	return 1;
}

uint8_t drivesystem_driveDEAMON()
{
	switch (mDSDStatus)
	{
	case 0:
		return 1;
		break;
	case 1:
		if(mDSDLinear == 0)
		{
			mDSDLinear = 1;
			mDSDTargetTime = mSysTimeMs + mTravelTime;
		}
		if (mSysTimeMs < mDSDTargetTime)
		{
			PORTD &= ~(0b10000000);
			PORTB |= (0b00000001);
			
			PORTB &= ~(0b00000010);
			PORTB |= (0b00000100);
		}
		else
		{
			PORTD |= (0b10000000);
			PORTB |= (0b00000001);
			PORTB |= (0b00000110);
			mDSDTargetTime = 0;
			mDSDLinear = 0;
			mDSDStatus &= ~(1);
		}
		break;
	case 2:
	case 3: // 3 or 2
		if(mDSDAngle == 0)
		{
			mDSDAngle = 1;
			mDSDTargetTime = mSysTimeMs + mAngleTravelTime;
		}
		if (mSysTimeMs < mDSDTargetTime)
		{
			if(mAngleDirection == 1)
			{
				PORTD &= ~(0b10000000);
				PORTB |= (0b00000001);
				
				PORTB &= ~(0b00000100);
				PORTB |= (0b00000010);
			}
			else
			{
				PORTD |= (0b10000000);
				PORTB &= ~(0b00000001);
				
				PORTB &= ~(0b00000010);
				PORTB |= (0b00000100);
			}
		}
		else
		{
			PORTD |= (0b10000000);
			PORTB |= (0b00000001);
			PORTB |= (0b00000110);
			mDSDTargetTime = 0;
			mDSDAngle = 0;
			mDSDStatus &= ~(2);
		}
		break;
		default:
		break;
	}
	return 1;
}
