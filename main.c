/*
 * main.c
 *
 *  Created on: ???/???/????
 *      Author: mohamed mousa
 */

#define F_CPU 8000000
#include "avr/delay.h"
#include "../bit_cal.h"
#include "../std_types.h"
#include "DIO_InterFace.h"
#include "LCD_InterFace.h"
#include "Uart_InterFace.h"

u8 message[20];
u8 key[20];
u8 rem[20];
u8 new_rem[20];

void get_key(void)
{
	for(u8 i =0 ; i<4 ; i++)
		{
			_delay_ms(30);
			key[i]=Uart_Receive_Char();
		}

}

int exor(int a,int b)
{
	if(a==b)
		return 0;
	else
		return 1;
}
void processing()
{
	for(u8 i=0; i<3; i++)
	{
		new_rem[i]=message[i+8];
	}

	LCD_Write_Cmd(0b00000001);
	u8 pr[]="Processing";
		LCD_Write_Pos(pr,3,0);
		_delay_ms(5000);
		for(int i=0;i<4-1;i++)
		message[8+i]=0;
		message[8+4-1]='\0';

		int codelen = 8+4-1;

		int temp[20];

		for(int i=0;i<4;i++)
		rem[i]=message[i];

		for(int j=4;j<=codelen;j++)
		{
		    for(int i=0;i<4;i++)
		    temp[i]=rem[i];

		    if(rem[0]==0)
		    {
		        for(int i=0;i<4-1;i++)
		            rem[i]=temp[i+1];
		    }
		    else
		    {
		        for(int i=0;i<4-1;i++)
		            rem[i]=exor(temp[i+1],key[i+1]);

		    }
		    if(j!=codelen)
		        rem[4-1]=message[j];
		    else
		        rem[4-1]='\0';
		}

		for(int i=0;i<4-1;i++)
		message[8+i]=rem[i];
		message[codelen]='\0';


		_delay_ms(5000);
		LCD_Write_Cmd(0b00000001);
			u8 arr[]="Your remainder:";
			LCD_Write_Pos(arr,0,0);
			for(u8 i=0;i<3;i++)
			{
				LCD_Write_Num(rem[i],i,1);
			}


		for(u8 i=0; i<3;i++)
		{
		if(rem[i]== new_rem[i])
		{
			_delay_ms(5000);
			LCD_Write_Cmd(0b00000001);
			u8 arr[]="Success message:";
			LCD_Write_Pos(arr,0,0);
			for(u8 i=0 ; i<8 ; i++)
			{
				LCD_Write_Num(message[i],i,1);
			}
		}
		else
		{
			_delay_ms(5000);
			LCD_Write_Cmd(0b00000001);
			u8 arr[]="error message:";
			LCD_Write_Pos(arr,0,0);
			for(u8 i=0 ; i<8 ; i++)
			{
				LCD_Write_Num(message[i],i,1);
			}
		}
	}

}




void Receiver(void)
{
	for(u8 i =0 ; i<11 ; i++)
	{
		_delay_ms(30);
		message[i]=Uart_Receive_Char();
	}
}

int main(void)
{
	DIO_SET_PIN_DIR(GROUP_D,PIN_0,DIO_INPUT);

	LCD_Inti();
	Uart_Init();
	u8 arr[]="Arrived Frame:";
	LCD_Write_Pos(arr,0,0);
	u8 flag=0;

	while(1)
	{
		if(flag==0)
		{
		Receiver();
		for(u8 i =0 ; i<11 ; i++)
				{
					LCD_Write_Num(message[i],i,1);
					_delay_ms(100);
				}
		_delay_ms(5000);
		flag++;
		}

		if(flag==1)
		{
			LCD_Write_Cmd(0b00000001);
			u8 arrrr[]="Arrived Key:";
			LCD_Write_Pos(arrrr,0,0);
			get_key();
			for(u8 i =0 ; i<4 ; i++)
			{
				LCD_Write_Num(key[i],i,1);
			_delay_ms(100);
			}
			_delay_ms(5000);
			flag++;
		}
		processing();
	return 0;
	}
}
