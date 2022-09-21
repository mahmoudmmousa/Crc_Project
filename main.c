/*
 * main.c
 *
 *  Created on: ???/???/????
 *      Author: mohamed mousa
 */


#define F_CPU 1600000
#include "avr/delay.h"
#include "../bit_cal.h"
#include "../std_types.h"
#include "DIO_InterFace.h"
#include "LCD_InterFace.h"
#include "Uart_InterFace.h"




u8 message[20];
u8 rem[20];
u8 full_message[12];
u8 key[20];



void Get_Message()
{
	u8 ent[]="Enter Message(8)";
	LCD_Write_Pos(ent,0,0);
	u8 x=0;
	u8 result;
	u8 result1;
	while(x<8)
	{
		DIO_GET_PIN_VALUE(GROUP_A,PIN_2,&result);
		_delay_ms(250);
		if(result==0)
		{
			LCD_Write_Num(1,x,1);
			message[x]=1;
			x++;
			_delay_ms(750);
		}
		DIO_GET_PIN_VALUE(GROUP_A,PIN_1,&result1);
		_delay_ms(250);
		if(result1==0)
		{
			LCD_Write_Num(0,x,1);
			message[x]=0;
			x++;
			_delay_ms(750);
		}
	}
	if(x==8)
	{
		x++;
		LCD_Write_Cmd(0b00000001);
		u8 arr[]="Your Message:";
		LCD_Write_Pos(arr,0,0);
		for(u8 i=0;i<8;i++)
		{
			LCD_Write_Num(message[i],i,1);
		}
	}
	_delay_ms(5000);
	LCD_Write_Cmd(0b00000001);
}
int exor(int a,int b)
{
	if(a==b)
		return 0;
	else
		return 1;
}

void Get_Divisor()
{
	u8 ent[]="Enter Divisor(4)";
	LCD_Write_Pos(ent,0,0);
	u8 x=0;
	u8 result;
	u8 result1;
		while(x<4)
		{
			DIO_GET_PIN_VALUE(GROUP_A,PIN_2,&result);
			_delay_ms(250);
			if(result==0)
			{
				LCD_Write_Num(1,x,1);
				key[x]=1;
				x++;
				_delay_ms(750);

			}
			DIO_GET_PIN_VALUE(GROUP_A,PIN_1,&result1);
			_delay_ms(250);
			if(result1==0)
			{
				LCD_Write_Num(0,x,1);
				key[x]=0;
				x++;
				_delay_ms(750);
			}
		}
		if(x==4)
		{
			x++;
			LCD_Write_Cmd(0b00000001);
			u8 arr[]="Your Divisor:";
			LCD_Write_Pos(arr,0,0);
			for(u8 i=0;i<4;i++)
			{
				LCD_Write_Num(key[i],i,1);
			}
		}
		_delay_ms(5000);
		LCD_Write_Cmd(0b00000001);
}

void processing()
{

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

		for(u8 i=0 ; i<8 ; i++)
					{
						full_message[i]=message[i];
					}

				for( u8 j=8 ; j<12 ; j++)
					{
						full_message[j]= rem[j-8];
					}

					_delay_ms(5000);
					LCD_Write_Cmd(0b00000001);
					u8 arr1[]="Full Message:";
					LCD_Write_Pos(arr1,0,0);
					for(u8 k=0;k<11;k++)
					{
						LCD_Write_Num(full_message[k],k,1);
						_delay_ms(100);
					}
}

void sender(void)
{
	for(u8 i=0; i <11 ; i++)
	{
		_delay_ms(30);
	Uart_Send_Char(full_message[i]);
	}

}

void send_key(void)
{
	for(u8 i=0; i <4 ; i++)
		{
			_delay_ms(30);
		Uart_Send_Char(key[i]);
		}
}

void main(void)
{
	DIO_SET_PIN_DIR(GROUP_A,PIN_2,DIO_INPUT);
	DIO_SET_PIN_VALUE(GROUP_A,PIN_2,DIO_HIGH);
	DIO_SET_PIN_DIR(GROUP_A,PIN_1,DIO_INPUT);
	DIO_SET_PIN_VALUE(GROUP_A,PIN_1,DIO_HIGH);
	DIO_SET_PIN_DIR(GROUP_D,PIN_1,DIO_OUTPUT);
	LCD_Inti();
	Uart_Init();

	Get_Message();
	Get_Divisor();
	processing();
	u8 flag=0;


	while(1)
	{
		if(flag==0)
		{
		sender();

		flag++;
		}
		_delay_ms(6000);
		if(flag==1)
		{
			LCD_Write_Cmd(0b00000001);
			u8 arr11[]="send key:";
			LCD_Write_Pos(arr11,0,0);
			for(u8 l=0;l<4;l++)
			{
			LCD_Write_Num(key[l],l,1);
			_delay_ms(250);
			}
			send_key();
			flag++;
		}
	}
}








