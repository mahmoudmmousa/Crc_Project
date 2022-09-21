/*
 * Uart_Private.h
 *
 *  Created on: ???/???/????
 *      Author: mohamed mousa
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define UDR *((u8*)0x2c)
#define UCSRA *((u8*)0x2B)
#define UCSRB *((u8*)0x2A)
#define UCSRC *((u8*)0x40)
#define UBRRL *((u8*)0x29)
#define UBRRH *((u8*)0x40)


#endif /* UART_PRIVATE_H_ */
