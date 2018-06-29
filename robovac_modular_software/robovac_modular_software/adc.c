/*
 * adc.c
 *
 * Created: 29.04.2017 20:35:45
 *  Author: febs
 */ 

#include <avr/io.h>

void adc_init(void){
	ADMUX = 0b00000000; //S.248 ff
	ADCSRA = 0b11100000;
	ADCSRB = 0b00000000;
	DIDR0 |= 0b00000001;
}

int adc_getvalue(void){
	unsigned char lval,hval;
	lval = ADCL;
	hval = ADCH;
	return lval + (hval<<8);	
}