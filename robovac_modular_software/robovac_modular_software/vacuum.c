/*
 * vacuum.c
 *
 * Created: 11.06.2018 23:01:28
 *  Author: feb
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

#include "globals.h"

uint8_t mVacuumState = 0;

uint8_t vacuum_init()
{
	DDRC |= 0b00000010;
	return 1;
}

uint8_t vacuum_getState()
{

	return mVacuumState;
}

uint8_t vacuum_setState(uint8_t motstate)
{
	mVacuumState = motstate;
	if (mVacuumState == 1 && mStatusFlag != 'A')
	{
		PORTC |= 0b00000010;
		return 1;	
	}
	else
	{
		PORTC &= ~(0b00000010);
		return 0;
	}
}
