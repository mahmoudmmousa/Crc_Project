/*
 * Program.c
 *
 *  Created on: ???/???/????
 *      Author: mohamed mousa
 */


#include "../bit_cal.h"
#include "../std_types.h"
#include "DIO_CONFIG.h"
#include "DIO_Private.h"
#include "DIO_Interface.h"

u8 DIO_SET_PIN_VALUE(u8 PORT_NB,u8 PIN_NB,u8 PIN_VALUE)
{
	u8 ERROR_STATE=0;
if(PORT_NB>= DIO_MAXPORT_NB)
{
	ERROR_STATE=1;
}
else if(PIN_VALUE !=DIO_HIGH && PIN_VALUE!=DIO_LOW )
{
	ERROR_STATE=1;
}
else
{
	switch(PORT_NB)
	{
	case GROUP_A:
	assign_bit(DIO_U8_PORTA,PIN_NB,PIN_VALUE);
	break;
	case GROUP_B:
	assign_bit(DIO_U8_PORTB,PIN_NB,PIN_VALUE);
	break;
	case GROUP_C:
	assign_bit(DIO_U8_PORTC,PIN_NB,PIN_VALUE);
	break;
	case GROUP_D:
	assign_bit(DIO_U8_PORTD,PIN_NB,PIN_VALUE);
	break;
	}
}
return ERROR_STATE;
}

u8 DIO_SET_PIN_DIR(u8 PORT_NB,u8 PIN_NB,u8 PIN_DIR)
{
	u8 ERROR_STATE=0;
if(PORT_NB>= DIO_MAXPORT_NB)
{
	ERROR_STATE=1;
}
else if(PIN_DIR !=DIO_INPUT && PIN_DIR!=DIO_OUTPUT)
{
	ERROR_STATE=1;
}
else
{
	switch(PORT_NB)
	{
	case GROUP_A:
	assign_bit(DIO_U8_DDRA,PIN_NB,PIN_DIR);
	break;
	case GROUP_B:
	assign_bit(DIO_U8_DDRB,PIN_NB,PIN_DIR);
	break;
	case GROUP_C:
	assign_bit(DIO_U8_DDRC,PIN_NB,PIN_DIR);
	break;
	case GROUP_D:
	assign_bit(DIO_U8_DDRD,PIN_NB,PIN_DIR);
	break;
	}
}
return ERROR_STATE;
}

u8 DIO_GET_PIN_VALUE(u8 PORT_NB,u8 PIN_NB,u8* PIN_VALUE)
{
	u8 ERROR_STATE=0;
if(PORT_NB>= DIO_MAXPORT_NB)
{
	ERROR_STATE=1;
}

else
{
	switch(PORT_NB)
	{
	case GROUP_A:
	 *PIN_VALUE=check_bit(DIO_U8_PINA,PIN_NB);
	break;
	case GROUP_B:
	*PIN_VALUE=check_bit(DIO_U8_PINB,PIN_NB);
	break;
	case GROUP_C:
	 *PIN_VALUE=check_bit(DIO_U8_PINC,PIN_NB);
	break;
	case GROUP_D:
	 *PIN_VALUE=check_bit(DIO_U8_PIND,PIN_NB);
	break;
	}
}
return ERROR_STATE;
}

u8 DIO_SET_PORT_VALUE(u8 PORT_NB,u8 PORT_VALUE)
{
	u8 ERROR_STATE=0;
if(PORT_NB>= DIO_MAXPORT_NB)
{
	ERROR_STATE=1;
}
else if(PORT_VALUE > DIO_MAXPORT_VALUE)
{
	ERROR_STATE=1;
}
else
{
	switch(PORT_NB)
	{
	case GROUP_A:
	DIO_U8_PORTA=PORT_VALUE;
	break;
	case GROUP_B:
	DIO_U8_PORTB=PORT_VALUE;
	break;
	case GROUP_C:
		DIO_U8_PORTC=PORT_VALUE;
	break;
	case GROUP_D:
		DIO_U8_PORTD=PORT_VALUE;
	break;
	}
}
return ERROR_STATE;
}

u8 DIO_SET_PORT_DIR(u8 PORT_NB,u8 PORT_DIR)
{
	u8 ERROR_STATE=0;
if(PORT_NB>= DIO_MAXPORT_NB)
{
	ERROR_STATE=1;
}
else if(PORT_DIR > DIO_MAXPORT_DIR)
{
	ERROR_STATE=1;
}
else
{
	switch(PORT_NB)
	{
	case GROUP_A:
	DIO_U8_DDRA=PORT_DIR;
	break;
	case GROUP_B:
	DIO_U8_DDRB=PORT_DIR;
	break;
	case GROUP_C:
		DIO_U8_DDRC=PORT_DIR;
	break;
	case GROUP_D:
		DIO_U8_DDRD=PORT_DIR;
	break;
	}
}
return ERROR_STATE;
}


