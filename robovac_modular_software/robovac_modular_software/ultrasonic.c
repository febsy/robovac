/*
 * ultrasonic.c
 *
 * Created: 29.04.2017 20:55:59
 *  Author: febs
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
//#include <avr/interrupt.h>
#include "ultrasonic.h"
#include "system_time.h"

#include "globals.h"


volatile char mUS1State = 0;
volatile char mUS2State = 0;
volatile unsigned long mUS1Time = 0; 
volatile unsigned long mUS2Time = 0;

void ultrasonic_init(void){
	DDRD |= 0b00010000;			//set triggerpin
}

int ultrasonic_transform(unsigned long traveltime){ // returns distance in cm
	unsigned long tt = (traveltime/2);
	int distance = (int)(0.0343 * tt);
	return distance;
}

uint8_t ultrasonic_getDistance(int16_t* dist1,int16_t* dist2) // call max. all 60 ms
{
		int d1 = ultrasonic_transform(mUS1Time);
		int d2 = ultrasonic_transform(mUS2Time);
		if (d1 > 400)
		{
			d1 = 400;
		}
		if (d2 > 400)
		{
			d2 = 400;
		}
		*dist1 = d1;
		*dist2 = d2;
		PORTD |= 0b00010000;
		_delay_us(20);
		PORTD &= ~0b00010000;
		mUS1Time = 0;
		mUS2Time = 0;
		mUS1State = 1;
		mUS2State = 1;
		return 1;
}

void ultrasonic_measureDEAMON(void)
{
	/*------------------------US1------------------------*/
	if(mUS1State == 1)
	{
		if((PIND & 0b00001000) == 0b00001000)
		{
			mUS1Time = system_time_GetUs();
			mUS1State = 2;
		}
	}
	if (mUS1State == 2)
	{
		if((PIND & 0b00001000) == 0b00000000)
		{
			unsigned long secondTimeUs1 = system_time_GetUs();
			if (secondTimeUs1 < mUS1Time)
			{
				secondTimeUs1 += 100000;
			}
			mUS1Time = secondTimeUs1 - mUS1Time;
			mUS1State = 0;
		}
	}
	/*------------------------US2------------------------*/
	if(mUS2State == 1)
	{
		if((PIND & 0b00000100) == 0b00000100)
		{
			mUS2Time = system_time_GetUs();
			mUS2State = 2;
		}
	}
	if (mUS2State == 2)
	{
		if((PIND & 0b00000100) == 0b00000000)
		{
			unsigned long secondTimeUs2 = system_time_GetUs();
			if (secondTimeUs2 < mUS2Time)
			{
				secondTimeUs2 += 100000;
			}
			mUS2Time = secondTimeUs2 - mUS2Time;
			mUS2State = 0;
		}
	}
}