/*
 * tracker.c
 *
 * Created: 11.06.2018 23:01:11
 *  Author: feb
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

uint8_t tracker_getPosition(uint8_t objmode,int16_t* x,int16_t* y,int16_t* a_h) // ObjectMode 0: Return X,Y,Angle ; ObjectMode 1: Return X,Y,Bool
{

	return 0;
}

uint8_t tracker_getUSDistance(int16_t* us1,int16_t* us2)
{

	return 0;
}

uint8_t tracker_setHome(int16_t x,int16_t y)
{

	return 0;
}

uint8_t tracker_setOrientation(int16_t a)
{

	return 0;
}

uint8_t tracker_setDistancePerUnit(int16_t dpu)
{

return 0;
}

uint8_t tracker_setAnglePerUnit(int16_t apu)
{

return 0;
}
