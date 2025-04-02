#include <REG52.H>
#include <stdio.h>
#define LCD_DataPort P0

// ????:
sbit LCD_RS = P2^6;
sbit LCD_RW = P2^5;
sbit LCD_EN = P2^7;

double value1 = 12.34;  // ????

// ????
void LCD_Delay() {
    unsigned char i, j;
    i = 2;
    j = 239;
    do {
        while (--j);
    } while (--i);
}

// ?????
void LCD_WriteCommand(unsigned char Command) {
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_DataPort = Command;
    LCD_EN = 1;
    LCD_Delay();
    LCD_EN = 0;
    LCD_Delay();
}

// ?????
void LCD_WriteData(unsigned char Data) {
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_DataPort = Data;
    LCD_EN = 1;
    LCD_Delay();
    LCD_EN = 0;
    LCD_Delay();
}

// ????????
void LCD_SetCursor(unsigned char Line, unsigned char Column) {
    if (Line == 1) {
        LCD_WriteCommand(0x80 | (Column - 1));
    } else if (Line == 2) {
        LCD_WriteCommand(0x80 | (Column - 1 + 0x40));
    }
}

// ??? LCD1602
void LCD_Init() {
    LCD_WriteCommand(0x38);  // 8?????,2???,5x7??
    LCD_WriteCommand(0x0C);  // ???,???,?????
    LCD_WriteCommand(0x06);  // ????,????+1
    LCD_WriteCommand(0x01);  // ??
}

// ?????
void LCD_ShowString(unsigned char Line, unsigned char Column, char *String) {
    unsigned char i;
    LCD_SetCursor(Line, Column);
    for (i = 0; String[i] != '\0'; i++) {
        LCD_WriteData(String[i]);
    }
}

void LCD_ShowFourValues(double value1, double value2, double value3, double value4) {
    char buffer[16];  // ???????????

    // ?????? (0,0)
    sprintf(buffer, "%.2f", value1);  // ? double ??????,??????
    LCD_ShowString(1, 1, buffer);     // ??1??1???

    // ?????? (0,8)
    sprintf(buffer, "%.2f", value2);  // ? double ??????,??????
    LCD_ShowString(1, 9, buffer);     // ??1??9???

    // ?????? (1,0)
    sprintf(buffer, "%.2f", value3);  // ? double ??????,??????
    LCD_ShowString(2, 1, buffer);     // ??2??1???

    // ?????? (1,8)
    sprintf(buffer, "%.2f", value4);  // ? double ??????,??????
    LCD_ShowString(2, 9, buffer);     // ??2??9???
}

void External0_ISR() interrupt 0 {
    // INT0 P3^2
    P1 = 0x00; 
}
// ???
void main(void) {
    double value2 = 56.78;  // ????
    double value3 = 90.12;  // ????
    double value4 = 34.56;  // ????


    LCD_Init(); 
	  IT0 = 1;
	  EX0 = 1;
	  EA = 1;

    // ?????
    LCD_ShowFourValues(value1, value2, value3, value4);

    while (1) {
        // ????????????
    }
}