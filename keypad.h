#ifndef KEYPAD_H
#define KEYPAD_H

#include <REG51.H>

#define KEYPAD_PORT P1

// Add key definitions
#define KEY_ENTER '='
#define KEY_CLEAR 'C'

unsigned char keypad_scan(void);

#endif