#include "keypad.h"
#include "delay.h"

unsigned char keypad_scan(void) {
    unsigned char row, col, key = 0;

    const char keys[4][4] = {
        { '7', '8', '9', '/' },
        { '4', '5', '6', '*' },
        { '1', '2', '3', '-' },
        { 'C', '0', '=', '+' }
    };

    for (row = 0; row < 4; row++) {
        KEYPAD_PORT = 0xFF;
        KEYPAD_PORT &= ~(1 << row);

        for (col = 0; col < 4; col++) {
            if (!(KEYPAD_PORT & (1 << (col + 4)))) {
                while (!(KEYPAD_PORT & (1 << (col + 4))));
                return keys[row][col];
            }
        }
    }
    return 0;
}