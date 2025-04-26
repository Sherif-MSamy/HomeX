#ifndef LCD_H
#define LCD_H

#include <REG51.H>
#include "i2c.h"

#define LCD_ADDR 0x40 // PCF8574 I2C address

void lcd_write(unsigned char dat, unsigned char rs);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char dat);
void lcd_string(unsigned char *str);
void lcd_init(void);

#endif