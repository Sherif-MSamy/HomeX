#include <REG51.H>
#include "uart.h"

/* UART Initialization */
void UART_Init(void) {
    TMOD |= 0x20;   // Timer1 in Mode 2 (8-bit auto-reload)
    TH1 = 0xFD;     // 9600 baud rate for 11.0592 MHz
    SCON = 0x50;    // 8-bit data, receive enabled
    TR1 = 1;        // Start Timer1
}

/* UART Receive Data */
char UART_Receive(void) {
    if (RI) {
        RI = 0;     // Clear receive interrupt flag
        return SBUF; // Return received data
    }
    return 0;
}