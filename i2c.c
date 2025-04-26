#include "i2c.h"
#include "delay.h"

void i2c_start(void) {
    SDA = 1;
    SCL = 1;
    SDA = 0;
    delay_ms(1);
    SCL = 0;
}

void i2c_stop(void) {
    SDA = 0;
    SCL = 1;
    SDA = 1;
    delay_ms(1);
}

void i2c_write(unsigned char dat) {
    unsigned char i;
    for (i = 0; i < 8; i++) {
        SDA = (dat & 0x80) ? 1 : 0;
        SCL = 1;
        delay_ms(1);
        SCL = 0;
        dat <<= 1;
    }
    SDA = 1; // Acknowledge bit
    SCL = 1;
    delay_ms(1);
    SCL = 0;
}