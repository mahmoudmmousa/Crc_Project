/*
 * Uart_InterFace.h
 *
 *  Created on: ???/???/????
 *      Author: mohamed mousa
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void Uart_Init(void);
void Uart_Send_Char(u8 Data);
u8 Uart_Receive_Char(void);
void Uart_Send_String(u8 *Str);
void Uart_Receive_String(u8 *Str);

#endif /* UART_INTERFACE_H_ */
