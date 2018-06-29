/*
 * robovac_modular_software.c
 *
 * Created: 10.02.2018 23:24:15
 * Author : feb
 */ 

#include <avr/io.h>
#include "hmc5843.h"
#include "ultrasonic.h"
#include "word_interpreter.h"
#include "usart0.h"

#include "globals.h"

volatile uint8_t mSoftReset;

void init(void);

int main(void)
{
    while(1)
	{
		init();
		mSoftReset = 0;
		while (mSoftReset == 0) 
		{
			word_interpreter_message_handler();
		}
	}
}

void init(void)
{
	usart0_init(9600);
	hmc5883_init();
	ultrasonic_init();	
}