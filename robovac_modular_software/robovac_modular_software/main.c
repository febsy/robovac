/*
 * robovac_modular_software.c
 *
 * Created: 10.02.2018 23:24:15
 * Author : feb
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "ultrasonic.h"
#include "hmc5843.h"
#include "ultrasonic.h"
#include "word_interpreter.h"
#include "usart0.h"
#include "adc.h"
#include "system_time.h"
#include "bms.h"
#include "drivesystem.h"
#include "tracker.h"

#include "globals.h"

volatile uint8_t mSoftReset;

void init(void);
void timer_init(void);

int main(void)
{
    while(1)
	{
		init();
		sei();
		mSoftReset = 0;
		while (mSoftReset == 0) 
		{
			word_interpreter_message_handler();
		}
		cli();
	}
}

void init(void)
{
	usart0_init(9600);
	hmc5883_init();
	ultrasonic_init();
	bms_init();
	timer_init();
	drivesystem_init(); 
	tracker_init();
}

void timer_init(void){
	TCCR0A = 0b00000010;
	TCCR0B = 0b10000010;
	OCR0A = 200;				//Compare Match; clk/8 prescaler; count to 2;
	TIMSK0 = 0b00000010;	//CTC A Interrupt enabled
}

ISR(TIMER0_COMPA_vect)
{
	system_time_IRQDeamon();
	ultrasonic_measureDEAMON();
	drivesystem_driveDEAMON();
}