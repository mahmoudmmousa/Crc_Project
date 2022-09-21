/*
 * LCD_InterFace.h
 *
 *  Created on: ???/???/????
 *      Author: mohamed mousa
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define LCD_Colum 16
#define LCD_Row 2

void LCD_Write_Cmd(u8 Cmd);
void LCD_Write_Data(u8 Data);
void LCD_Write(u8 Value);
void LCD_Inti(void);
u8 LCD_Write_Pos(u8 *Data, u8 x_pos, u8 y_pos);
void LCD_Write_Num(u32 num,u8 x_pos, u8 y_pos);




#endif /* LCD_INTERFACE_H_ */
