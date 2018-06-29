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


#ifndef USART0_H
#define USART0_H


#include <stdint.h>


extern void usart0_init(unsigned long baud);
extern void usart0_finalize(void);
extern void usart0_putchar(char c);
extern char usart0_getchar(void);
extern char usart0_flush(void);

extern void usart0_puts(char *s);
extern char *usart0_gets(char *s, int size);


#endif /* USART0_H */
