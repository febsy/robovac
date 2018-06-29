/*******************************************************************************
 *
 * Copyright (C) 2015, Pluess Jonas
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 ******************************************************************************/


#include <avr/io.h>

#include "usart0.h"


#define ENABLE_USART0_DOUBLESPEED 1


// initialize usart, set baud rate
extern void usart0_init(unsigned long baud)
{
	// enable or disable double speed mode and calculate baudrate
	unsigned int ubrr;
	if(ENABLE_USART0_DOUBLESPEED){
		ubrr = (F_CPU/(8UL * (unsigned long)baud)) -1;
		UCSR0A = (1<<U2X0);
	}else{
		ubrr = (F_CPU/(16UL * (unsigned long)baud)) -1;
	}

	// set baudrade
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)(ubrr);

	// enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	// set frame format
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

// disable usart receiver and transmitter
extern void usart0_finalize(void)
{
	UCSR0B = 0;
}

// send one byte
extern void usart0_putchar(char c)
{
	while(!(UCSR0A & (1<<UDRE0))){
		/* wait until transmit buffer is empty */
	}
	UDR0 = c;
}

// receive one byte
extern char usart0_getchar(void)
{
	while(!(UCSR0A & (1<<RXC0))){
		/* wait until receive flag is set */
	}
	return UDR0;
}

// flush usart receive buffer
extern char usart0_flush(void)
{
	char dummy = 0;
	while(UCSR0A & (1<<RXC0)){
		dummy = UDR0;
	}
	return dummy; // not needed just call like extern void usart0_flush(void)
}

// send a string without line end
extern void usart0_puts(char *s)
{
	unsigned int i = 0;
	while(s[i] != '\0'){
		usart0_putchar(s[i]);
		i++;
	}
}

// receive a string with length size
extern char *usart0_gets(char *s, int size)
{
//	unsigned int i = 0;
//	for(i = 0; i < (size-1); i++){
//		s[i] = usart0_getchar();
//	}
//	s[size-1] = '\0';
//	return s;
	uint8_t NextChar;
	uint8_t StringLen = 0;

	NextChar = usart0_getchar();         // Warte auf und empfange das nächste Zeichen

	// Sammle solange Zeichen, bis:
	// * entweder das String Ende Zeichen kam
	// * oder das aufnehmende Array voll ist
	while( NextChar != '\n' && StringLen < size - 1 ) {
		*s++ = NextChar;
		StringLen++;
		NextChar = usart0_getchar();
	}
	*s = '\0';
	return s;
}
