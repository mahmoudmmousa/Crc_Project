/*
 * DIO_InterFace.h
 *
 *  Created on: ???/???/????
 *      Author: mohamed mousa
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


#define DIO_MAXPORT_NB  4
#define DIO_MAXPIN_NB  8
#define DIO_HIGH 1
#define DIO_LOW 0
#define GROUP_A 0
#define GROUP_B 1
#define GROUP_C 2
#define GROUP_D 3
#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7

#define DIO_INPUT 0
#define DIO_OUTPUT 1
#define DIO_MAXPORT_VALUE 255
#define DIO_MAXPORT_DIR 255
 u8 DIO_SET_PIN_VALUE(u8 PORT_NB,u8 PIN_NB,u8 PIN_VALUE);
 u8 DIO_SET_PIN_DIR(u8 PORT_NB,u8 PIN_NB,u8 PIN_DIR);
 u8 DIO_SET_PORT_VALUE(u8 PORT_NB,u8 PORT_VALUE);
 u8 DIO_SET_PORT_DIR(u8 PORT_NB,u8 PORT_DIR);
 u8 DIO_GET_PIN_VALUE(u8 PORT_NB,u8 PIN_NB,u8* PIN_VALUE);
 u8 DIO_GET_PORT_VALUE(u8 PORT_NB,u8* PORT_VALUE);



#endif /* DIO_INTERFACE_H_ */
