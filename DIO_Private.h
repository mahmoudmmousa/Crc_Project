/*
 * DIO_Private.h
 *
 *  Created on: ???/???/????
 *      Author: mohamed mousa
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

// Port A
#define DIO_U8_DDRA *((u8*)0x3A)
#define DIO_U8_PORTA *((u8*)0x3B)
#define DIO_U8_PINA *((u8*)0x39)



// Port B
#define DIO_U8_DDRB *((u8*)0x37)
#define DIO_U8_PORTB *((u8*)0x38)
#define DIO_U8_PINB *((u8*)0x36)

// Port C
#define DIO_U8_DDRC *((u8*)0x34)
#define DIO_U8_PORTC *((u8*)0x35)
#define DIO_U8_PINC *((u8*)0x33)


// Port D
#define DIO_U8_DDRD *((u8*)0x31)
#define DIO_U8_PORTD *((u8*)0x32)
#define DIO_U8_PIND *((u8*)0x30)



#endif /* DIO_PRIVATE_H_ */
