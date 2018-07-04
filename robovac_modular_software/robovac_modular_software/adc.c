/*
 * adc.c
 *
 * Created: 29.04.2017 20:35:45
 *  Author: febs
 */ 

#include <avr/io.h>

uint8_t adc_init(void){
	ADMUX = 0b00000000; //S.248 ff
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
	DIDR0 |= 0b00000001;
	return 0;
}

int16_t adc_getvalue(void){
	ADMUX = (ADMUX & 0xF0) | (0x00 & 0x0F);
	ADCSRA |= (1<<ADSC);
	while( ADCSRA & (1<<ADSC) );
	unsigned char lval,hval;
	lval = ADCL;
	hval = ADCH;
	return lval + (hval<<8);	
}