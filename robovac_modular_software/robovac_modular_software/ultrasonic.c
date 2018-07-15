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


volatile char mUSState = 0; // [0b<us2_eoc><us1_eoc>xxxx<us2><us1>]
volatile unsigned long mUS1Time = 0; 
volatile unsigned long mUS2Time = 0;

void ultrasonic_init(void){
	DDRD |= 0b00010000;			//set triggerpin
}

int ultrasonic_transform(unsigned long traveltime){
	unsigned long tt = (traveltime/2);
	int distance = (int)(0.0343 * tt);
	return distance;
}

uint8_t ultrasonic_getDistance(uint8_t* dist1,uint8_t* dist2)
{
	if(mUSState == 0)
	{
		//int d1 = ultrasonic_transform(mUS1Time);
		int d2 = ultrasonic_transform(mUS2Time);
		/*if (d1 > 253)
		{
			d1 = 0xFF;
		}*/
		if (d2 > 253)
		{
			d2 = 0xFF;
		}
		//*dist1 = d1;
		*dist2 = d2;
		PORTD |= 0b00010000;
		_delay_us(20);
		PORTD &= ~0b00010000;
		mUS1Time = 0;
		mUS2Time = 0;
		mUSState = 1;
		return 1;
	}
	return -1;
}

void ultrasonic_measureDEAMON(void)
{
	/*if((mUSState & 0b00000001) == 0){
		if((PIND & 0b00001000)== 0b00001000){
			mUS1Time -= mSysTimeMs;
			mUSState |= 0b00000001;
		}
	}*/
	if(mUSState == 1)
	{
		if((PIND & 0b00000100) == 0b00000100)
		{
			mUS2Time = system_time_GetUs();
			mUSState = 2;
		}
	}
	if (mUSState == 2)
	{
		if((PIND & 0b00000100) == 0b00000000)
		{
			unsigned long secondTimeUs2 = system_time_GetUs();
			if (secondTimeUs2 < mUS2Time)
			{
				secondTimeUs2 += 100000;
			}
			mUS2Time = secondTimeUs2 - mUS2Time;
			mUSState = 0;
		}
	}
}

/*

char message_def2[10];
snprintf(message_def2,sizeof(message_def2),"%d\n",(int)(mUS2Time/1000));
usart0_puts(message_def2);

*/