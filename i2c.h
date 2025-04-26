#ifndef I2C_H
#define I2C_H

#include <REG51.H>

sbit SDA = P0^4;
sbit SCL = P0^5;

void i2c_start(void);
void i2c_stop(void);
void i2c_write(unsigned char dat);

#endif