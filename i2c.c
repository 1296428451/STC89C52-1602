#include "i2c.h"
#include <REG52.H>
sbit I2C_SCL = P2^1;  // I2C ???
sbit I2C_SDA = P2^0;  // I2C ???
// I2C ????
void I2C_Delay() {
    unsigned char i = 10;  // ????
    while (--i);
}

// I2C ????
void I2C_Start() {
    I2C_SDA = 1;
    I2C_SCL = 1;
    I2C_Delay();
    I2C_SDA = 0;
    I2C_Delay();
    I2C_SCL = 0;
}

// I2C ????
void I2C_Stop() {
    I2C_SDA = 0;
    I2C_SCL = 1;
    I2C_Delay();
    I2C_SDA = 1;
    I2C_Delay();
}

// I2C ????
void I2C_SendByte(unsigned char byte) {
    unsigned char i;
    for (i = 0; i < 8; i++) {
        I2C_SDA = (byte & 0x80) ? 1 : 0;  // ?????
        byte <<= 1;
        I2C_SCL = 1;
        I2C_Delay();
        I2C_SCL = 0;
        I2C_Delay();
    }
    I2C_SDA = 1;  // ?? SDA,??????
    I2C_SCL = 1;
    I2C_Delay();
    I2C_SCL = 0;
}

// I2C ????
unsigned char I2C_ReceiveByte() {
    unsigned char i, byte = 0;
    I2C_SDA = 1;  // ?? SDA
    for (i = 0; i < 8; i++) {
        I2C_SCL = 1;
        I2C_Delay();
        byte = (byte << 1) | I2C_SDA;  // ????
        I2C_SCL = 0;
        I2C_Delay();
    }
    return byte;
}

// I2C ??????
void I2C_SendAck(unsigned char ack) {
    I2C_SDA = ack;
    I2C_SCL = 1;
    I2C_Delay();
    I2C_SCL = 0;
    I2C_Delay();
}

// I2C ??????
unsigned char I2C_ReceiveAck() {
    unsigned char ack;
    I2C_SDA = 1;  // ?? SDA
    I2C_SCL = 1;
    I2C_Delay();
    ack = I2C_SDA;
    I2C_SCL = 0;
    I2C_Delay();
    return ack;
}