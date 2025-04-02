#include "lcd.h"
#include "i2c.h"

#define LCD_ADDRESS 0x27  // ???????????

// LCD ???
void LCD_Init() {
    LCD_WriteCommand(0x33);  // ??? 8 ???
    LCD_WriteCommand(0x32);  // ??? 4 ???
    LCD_WriteCommand(0x28);  // 4 ???,2 ???,5x7 ??
    LCD_WriteCommand(0x0C);  // ???,???,?????
    LCD_WriteCommand(0x06);  // ????,????+1
    LCD_WriteCommand(0x01);  // ??
}

// ??????
void LCD_SetCursor(unsigned char Line, unsigned char Column) {
    if (Line == 1) {
        LCD_WriteCommand(0x80 | (Column - 1));
    } else if (Line == 2) {
        LCD_WriteCommand(0x80 | (Column - 1 + 0x40));
    }
}

// ???? LCD
void LCD_WriteCommand(unsigned char Command) {
    LCD_Send(0x00, Command);  // RS = 0 ????
}

// ???? LCD
void LCD_WriteData(unsigned char Data) {
    LCD_Send(0x01, Data);  // RS = 1 ????
}

// ?????
void LCD_ShowString(unsigned char Line, unsigned char Column, char *String) {
    unsigned char i;
    LCD_SetCursor(Line, Column);
    for (i = 0; String[i] != '\0'; i++) {
        LCD_WriteData(String[i]);
    }
}

// ???????? LCD
void LCD_Send(unsigned char rs, unsigned char da) {
    unsigned char high = da & 0xF0;  // ? 4 ?
    unsigned char low = (da << 4) & 0xF0;  // ? 4 ?

    I2C_Start();
    I2C_SendByte(LCD_ADDRESS << 1);  // ??????(???)
    I2C_SendByte(high | rs | 0x04 | 0x08);  // ? 4 ? + RS + EN + ??
    I2C_SendByte(high | rs | 0x00 | 0x08);  // ? 4 ? + RS + ??
    I2C_SendByte(low | rs | 0x04 | 0x08);   // ? 4 ? + RS + EN + ??
    I2C_SendByte(low | rs | 0x00 | 0x08);   // ? 4 ? + RS + ??
    I2C_Stop();
}