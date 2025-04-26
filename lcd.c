#include "lcd.h"
#include "delay.h"

void lcd_write(unsigned char dat, unsigned char rs) {
    unsigned char temp = dat & 0xF0;
    temp |= (rs << 0);
    temp |= (1 << 2);
    i2c_start();
    i2c_write(LCD_ADDR);
    i2c_write(temp);
    temp &= ~(1 << 2);
    i2c_write(temp);
    i2c_stop();

    temp = (dat << 4) & 0xF0;
    temp |= (rs << 0);
    temp |= (1 << 2);
    i2c_start();
    i2c_write(LCD_ADDR);
    i2c_write(temp);
    temp &= ~(1 << 2);
    i2c_write(temp);
    i2c_stop();
}

void lcd_cmd(unsigned char cmd) {
    lcd_write(cmd, 0);
    delay_ms(2);
}

void lcd_data(unsigned char dat) {
    lcd_write(dat, 1);
    delay_ms(2);
}

void lcd_string(unsigned char *str) {
    while (*str)
        lcd_data(*str++);
}

void lcd_init(void) {
    lcd_cmd(0x33); // Initialize LCD in 4-bit mode
    lcd_cmd(0x32); // Set to 4-bit mode
    lcd_cmd(0x28); // 4-bit, 2-line, 5x7 dots
    lcd_cmd(0x0C); // Display ON, Cursor OFF
    lcd_cmd(0x06); // Entry mode
    lcd_cmd(0x01); // Clear display
}