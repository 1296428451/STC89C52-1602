#ifndef _LCD_H_
#define _LCD_H_

// ????
void LCD_Init();
void LCD_SetCursor(unsigned char Line, unsigned char Column);
void LCD_WriteCommand(unsigned char Command);
void LCD_WriteData(unsigned char Data);
void LCD_ShowString(unsigned char Line, unsigned char Column, char *String);
void LCD_Send(unsigned char rs, unsigned char da);

#endif