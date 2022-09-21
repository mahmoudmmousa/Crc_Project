/*
 * LCD_Program.c
 *
 *  Created on: ???/???/????
 *      Author: mohamed mousa
 */

#include "../bit_cal.h"
#include "../std_types.h"
#define F_CPU 1600000
#include "avr/delay.h"
#include "DIO_InterFace.h"
#include "LCD_Config.h"
#include "LCD_Private.h"
#include "LCD_InterFace.h"


void LCD_Write_Cmd(u8 Cmd)
{
	DIO_SET_PIN_VALUE(LCD_Control_Port,LCD_RS_PIN,DIO_LOW);
	LCD_Write(Cmd);
}

void LCD_Write_Data(u8 Data)
{
	DIO_SET_PIN_VALUE(LCD_Control_Port,LCD_RS_PIN,DIO_HIGH);
	LCD_Write(Data);
}

void LCD_Write(u8 Value)
{
	DIO_SET_PIN_VALUE(LCD_Control_Port,LCD_RW_PIN,DIO_LOW);

	for(u8 i=0; i<8;i++)
	{
	DIO_SET_PIN_VALUE(LCD_DATA_Port,i,check_bit(Value,i));
	}

	DIO_SET_PIN_VALUE(LCD_Control_Port,LCD_E_PIN,DIO_HIGH);
	_delay_ms(1);
	DIO_SET_PIN_VALUE(LCD_Control_Port,LCD_E_PIN,DIO_LOW);
}

void LCD_Inti(void)
{
	DIO_SET_PORT_DIR(LCD_DATA_Port,DIO_MAXPORT_VALUE);
	DIO_SET_PIN_DIR(LCD_Control_Port,LCD_RS_PIN,DIO_OUTPUT);
	DIO_SET_PIN_DIR(LCD_Control_Port,LCD_RW_PIN,DIO_OUTPUT);
	DIO_SET_PIN_DIR(LCD_Control_Port,LCD_E_PIN,DIO_OUTPUT);
	_delay_ms(40);
	LCD_Write_Cmd(0b00111000);
	_delay_us(50);
	LCD_Write_Cmd(0b00001100);
	_delay_us(50);
	LCD_Write_Cmd(0b00000001);
	_delay_ms(2);
}



u8 LCD_Write_Pos(u8 *Data, u8 x_pos, u8 y_pos)
{
	u8 Error_State =0;
	u8 DDRAM_Address;
	if((x_pos < LCD_Colum) && (y_pos < LCD_Row))
	{
		DDRAM_Address = x_pos + (y_pos *64);
		DDRAM_Address = DDRAM_Address | 0b10000000;
		LCD_Write_Cmd(DDRAM_Address);

		while(*Data != '\0')
		{
			if(DDRAM_Address == 144)
			{
				DDRAM_Address =192;
				LCD_Write_Cmd(DDRAM_Address);
			}
			LCD_Write_Data(*Data);
			Data++;
			DDRAM_Address++;
		}
	}
	else
	{
		Error_State=1;
	}
	return Error_State;
}


void LCD_Write_Num(u32 num,u8 x_pos, u8 y_pos)
{
	u8 rem;
	u8 str[30];
	u8 arr_index=0;
	if(num == 0)
	{
		str[arr_index] = '0';
		arr_index++;
	}
	while(num !=0)
	{
	rem=num%10;
	str[arr_index]= rem+'0';
	arr_index++;
	num=num/10;
	}
	str[arr_index]='\0';
	reverse(str,arr_index);
	LCD_Write_Pos(str, x_pos, y_pos);
}


void reverse(u8 *ptr, u8 length)
{
	u8 start=0;
	u8 end=length -1;

	while(start< end)
	{
	swap(& ptr[start],& ptr[end]);
	start++;
	end--;
	}
}

void swap(u8 * a,u8 *b)
{
	u8 z=*a;
	*a=*b;
	*b=z;
}
