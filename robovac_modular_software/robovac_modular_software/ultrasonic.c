/*
 * ultrasonic.c
 *
 * Created: 29.04.2017 20:55:59
 *  Author: febs
 */ 

#include <avr/io.h>
#include <util/delay.h>
//#include <avr/interrupt.h>
#include "ultrasonic.h"


volatile unsigned long us1_time, us2_time;
volatile char us1_done = 2;
volatile char us2_done = 2;
volatile int us1_distance=100,us2_distance=100;

void ultrasonic_init(void){
	DDRD |= 0b00010000;			//set triggerpin
}

int ultrasonic_transform(unsigned long traveltime){
	unsigned long tt = (traveltime/2);
	int distance = (int)(0.343 * tt);
	return distance;
}

void ultrasonic_startmeasurement(void){
	if((us1_done == 2)&&(us2_done == 2)){
	PORTD |= 0b00010000;
	_delay_us(20);
	PORTD &= ~0b00010000;
	us1_done = 0;
	us2_done = 0;
	}
}

void ultrasonic_getdistance(void){
	if(us1_done == 0){
		if((PIND & 0b00001000)== 0b00001000){
			us1_time = runtime_us;
			us1_done = 1;
		}
	}
	if(us1_done == 1){
		if(((PIND & 0b00001000)== 0x00000000)){
			us1_time = runtime_us-us1_time;
			us1_done = 2;
			us1_distance = (int)(us1_time/58);
		}
	}
	if(us2_done == 0){
		if((PIND & 0b00000100)== 0b00000100){
			us2_time = runtime_us;
			us2_done = 1;
		}
	}
	if(us2_done == 1){
		if(((PIND & 0b00000100)== 0x00000000)){
			us2_time = runtime_us-us2_time;
			us2_done = 2;
			us2_distance = (int)(us2_time/58);
		}
	}
}