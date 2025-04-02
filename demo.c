#include <stdio.h>
#include <REG52.H>
#include <lcd.h>

sbit low = P0^2;
sbit high = P0^3;
sbit but = P0^7;

double value1 = 12.34;  
double value2 = 56.78;  
double value3 = 90.12; 
double value4 = 34.56;  

void LCD_ShowFourValues(double value1, double value2, double value3, double value4) {
    char buffer[16];

    //  (0,0)
    sprintf(buffer, "%.2f", value1);  // double
    LCD_ShowString(1, 1, buffer);     // 

    //  (0,8)
    sprintf(buffer, "%.2f", value2);  // double 
    LCD_ShowString(1, 9, buffer);     // 

    //  (1,0)
    sprintf(buffer, "%.2f", value3);  // double 
    LCD_ShowString(2, 1, buffer);     // 

    //  (1,8)
    sprintf(buffer, "%.2f", value4);  // double
    LCD_ShowString(2, 9, buffer);     // 
}

void main(void) {
    LCD_Init();  // LCD1602
	  IT0 = 0;
	  EX0 = 1;
	  EA = 1;
	  low = 0;
	  high = 1;
    while (1) {
        LCD_ShowFourValues(value1, value2, value3, value4); 
			  if (but == 1) {
          value1+=1;
        }
				if (but == 0) {
          value1-=1;
        }
    }
}