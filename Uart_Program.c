/*
 * Uart_Program.c
 *
 *  Created on: ???/???/????
 *      Author: mohamed mousa
 */

#include "../bit_cal.h"
#include "../std_types.h"
#define F_CPU 8000000
#include "avr/delay.h"
#include "DIO_InterFace.h"
#include "Uart_Private.h"


void Uart_Init(void)
{
	UBRRH=0;
	UBRRL=51;// EQU=9600

	UCSRC=0b10000110;

	UCSRB=0b00011000;
}

void Uart_Send_Char(u8 Data)
{
	while(check_bit(UCSRA,5)==0);
	UDR=Data;
}

u8 Uart_Receive_Char(void)
{
	while(check_bit(UCSRA,7)==0);
	return UDR;
}

void Uart_Send_String(u8 *Str)
{
	while(*Str !='\0')
	{
		Uart_Send_Char(*Str);
		Str++;
	}
}

void Uart_Receive_String(u8 *Str)
{
	u8 i=0;
	while(i<8)
	{
	Str[i]=Uart_Receive_Char();
	i++;
	}
	Str[i]='\0';
}
